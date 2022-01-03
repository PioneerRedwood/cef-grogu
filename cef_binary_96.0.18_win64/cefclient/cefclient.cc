// Copyright (c) 2015 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include <windows.h>

#include <memory>

#include "include/cef_command_line.h"
// #include "include/cef_sandbox_win.h"

#include "cefclient/browser/main_context_impl.h"
// #include "cefclient/browser/main_message_loop_multithreaded_win.h"
#include "cefclient/browser/root_window_manager.h"
#include "cefclient/tests/test_runner.h"

#include "cefclient/browser/client_app_browser.h"
// #include "cefclient/browser/main_message_loop_external_pump.h"
#include "cefclient/browser/main_message_loop_std.h"
#include "cefclient/common/client_switches.h"
// #include "cefclient/renderer/client_app_renderer.h"
#include "cefclient/network/boost_test.h"

namespace client {
namespace {

int RunMain(HINSTANCE hInstance, int nCmdShow) {
  // Enable High-DPI support on Windows 7 or newer.
  CefEnableHighDPISupport();

  CefMainArgs main_args(hInstance);

  CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
  command_line->InitFromString(::GetCommandLineW());

  CefRefPtr<CefApp> app = new ClientAppBrowser();

  int exit_code = CefExecuteProcess(main_args, app, nullptr);
  if (exit_code >= 0)
    return exit_code;

  auto context = std::make_unique<MainContextImpl>(command_line, true);

  CefSettings settings;

  // Applications should specify a unique GUID here to enable trusted downloads.
  CefString(&settings.application_client_id_for_file_scanning)
      .FromString("9A8DE24D-B822-4C6C-8259-5A848FEA1E68");

  // Populate the settings based on command line arguments.
  context->PopulateSettings(&settings);

  // Create the main message loop object.
  std::unique_ptr<MainMessageLoop> message_loop;
  message_loop.reset(new MainMessageLoopStd);

  // Initialize CEF.
  context->Initialize(main_args, settings, app, nullptr);

  // Register scheme handlers.
  test_runner::RegisterSchemeHandlers();

  auto window_config = std::make_unique<RootWindowConfig>();
  window_config->always_on_top =
      command_line->HasSwitch(switches::kAlwaysOnTop);
  window_config->with_controls =
      !command_line->HasSwitch(switches::kHideControls);
  window_config->with_osr =
      settings.windowless_rendering_enabled ? true : false;

  // Create the first window.
  context->GetRootWindowManager()->CreateRootWindow(std::move(window_config));
  
  //client::network::LittleTimer timer(static_cast<uint32_t>(1));
  //timer.Start();

  // Run the message loop. This will block until Quit() is called by the
  // RootWindowManager after all windows have been destroyed.
  int result = message_loop->Run();

  // Shut down CEF.
  context->Shutdown();

  // Release objects in reverse order of creation.
  message_loop.reset();
  context.reset();

  return result;
}

}  // namespace
}  // namespace client

// Program entry point function.
int APIENTRY wWinMain(HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPTSTR lpCmdLine,
                      int nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);
  return client::RunMain(hInstance, nCmdShow);
}
