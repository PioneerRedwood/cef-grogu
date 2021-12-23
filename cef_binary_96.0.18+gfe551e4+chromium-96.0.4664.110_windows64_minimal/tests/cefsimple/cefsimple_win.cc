// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include <windows.h>

#include "include/cef_command_line.h"
// #include "include/cef_sandbox_win.h"
// #include "tests/cefsimple/simple_app.h"
#include "tests/cefsimple/context/main_context.h"
// #include "tests/cefsimple/context/main_message_loop_multithreaded.h"
// #include "tests/cefsimple"
#include "tests/cefsimple/browser/root_window_manager.h"
// #include "tests/cefsimple/tests/test_runner.h"

#include "tests/shared/browser/client_app_browser.h"

// Entry point function for all processes.
int APIENTRY wWinMain(HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPTSTR lpCmdLine,
                      int nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  CefEnableHighDPISupport();

  CefMainArgs main_args(hInstance);

  CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
  command_line->InitFromString(::GetCommandLineW());

  int exit_code = CefExecuteProcess(main_args, nullptr, nullptr);
  if (exit_code >= 0) {
    return exit_code;
  }

  auto context = std::make_unique<MainContext>(command_line, true);

  CefSettings settings;

  if (command_line->HasSwitch("enable-chrome-runtime")) {
    settings.chrome_runtime = true;
  }

  // Applications should specify a unique GUID here to enable trusted downloads.
  CefString(&settings.application_client_id_for_file_scanning)
      .FromString("9A8DE24D-B822-4C6C-8259-5A848FEA1E68");

  // Populate the settings based on command line arguments.
  context->PopulateSettings(&settings);

  // CefRefPtr<SimpleApp> app(new SimpleApp);
  CefRefPtr<CefApp> app = new ClientAppBrowser();

  // Create the main message loop object.
  std::unique_ptr<MainMessageLoop> message_loop;
  message_loop.reset(new MainMessageLoopStd);

  // Initialize CEF.
  context->Initialize(main_args, settings, app, nullptr);

  // Register scheme handlers.
  // test_runner::RegisterSchemeHandlers();

  // 창 설정
  auto window_config = std::make_unique<RootWindowConfig>();
  window_config->always_on_top = command_line->HasSwitch(switches::kAlwaysOnTop);
  window_config->with_controls = !command_line->HasSwitch(switches::kHideControls);
  // we don't need it
  // window_config->with_osr = settings.windowless_rendering_enabled ? true : false; 

  // Create the first window.
  context->GetRootWindowManager()->CreateRootWindow(std::move(window_config));

  // Run the message loop. This will block until Quit() is called by the
  // RootWindowManager after all windows have been destroyed.
  int result = message_loop->Run();

  // Shut down CEF.
  context->Shutdown();

  // Release objects in reverse order of creation.
  message_loop.reset();
  context.reset();

  return result;

  return 0;
}
