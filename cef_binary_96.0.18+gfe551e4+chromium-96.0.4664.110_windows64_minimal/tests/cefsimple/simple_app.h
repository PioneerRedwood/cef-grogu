// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
#define CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_

#include "include/cef_app.h"

// Implement application-level callbacks for the browser process.
// 브라우저 프로세스에서 어플리케이션 레벨의 콜백을 구현
// 아래는 두개의 가상클래스 상속 메서드, 두 클래스 모두 include 밑에 있음
// CefApp 
// - OnBeforeCommandLineProcessing() 명령줄이 처리되기 전에 호출
// - OnRegisterCustomSchemes() 커스텀 스키마를 등록할 수 있게
// - GetResourceBundleHandler() 리소스 번들 핸들러
// - GetBrowserProcessHandler() 브라우저 프로세스 핸들러
// - GetRenderProcessHandler() 렌더러 프로세스 핸들러

// CefBrowserProcessHandler 브라우저 프로세스 핸들러
// - OnContextInitialized() 컨텐스트 초기화 시
// - OnBeforeChildProcessLaunch() 자식 프로세스 실행 전에
// - OnScheduleMessagePumpWork() 스케줄 메시지 펌프
// - GetDefaultClient()
class SimpleApp : public CefApp, public CefBrowserProcessHandler {
 public:
  SimpleApp();

  // CefApp methods:
  CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override {
    return this;
  }

  // CefBrowserProcessHandler methods:
  void OnContextInitialized() override;
  CefRefPtr<CefClient> GetDefaultClient() override;

 private:
  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(SimpleApp);
};

#endif  // CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
