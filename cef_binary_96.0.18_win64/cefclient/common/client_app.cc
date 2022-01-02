// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "cefclient/common/client_app.h"
#include "cefclient/common/scheme_test_common.h" // for scheme test

#include "include/cef_command_line.h"

namespace client {

namespace {

// These flags must match the Chromium values.
const char kProcessType[] = "type";
const char kRendererProcess[] = "renderer";
#if defined(OS_LINUX)
const char kZygoteProcess[] = "zygote";
#endif

}  // namespace

ClientApp::ClientApp() {}

// static
ClientApp::ProcessType ClientApp::GetProcessType(
    CefRefPtr<CefCommandLine> command_line) {
  // The command-line flag won't be specified for the browser process.
  if (!command_line->HasSwitch(kProcessType))
    return BrowserProcess;

  const std::string& process_type = command_line->GetSwitchValue(kProcessType);
  if (process_type == kRendererProcess)
    return RendererProcess;
  return OtherProcess;
}

void ClientApp::OnRegisterCustomSchemes(
    CefRawPtr<CefSchemeRegistrar> registrar) {
  RegisterCustomSchemes(registrar);
}

// static
void ClientApp::RegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) {
  // 2022-01-02 지금은 스키마 테스트 안함
  // scheme_test::RegisterCustomSchemes(registrar);
}

}  // namespace client