#include <string>

#include <include/cef_browser.h>
#include <include/cef_command_line.h>
#include <include/wrapper/cef_helpers.h>
#include <include/wrapper/cef_message_router.h>

#include "qcview/common/protocol.h"
#include "qcview/browser/browser_app.h"

namespace qcview {
namespace {

class BrowserDelegate : public QCefViewBrowserApp::Delegate  {
public:
  BrowserDelegate() {}

  void OnContextInitialized(CefRefPtr<QCefViewBrowserApp> app) override { 

  }

  void OnBeforeChildProcessLaunch(CefRefPtr<QCefViewBrowserApp> app,
                                          CefRefPtr<CefCommandLine> command_line) override {

  }

private:
  IMPLEMENT_REFCOUNTING(BrowserDelegate);
};

} // namespace 

void QCefViewBrowserApp::CreateDelegates(DelegateSet& delegates) {
  delegates.insert(new BrowserDelegate());
}


QCefViewBrowserApp::QCefViewBrowserApp(const CefString& name)
  : bridge_object_name_(name)
{}

QCefViewBrowserApp::~QCefViewBrowserApp() {}

void QCefViewBrowserApp::OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line) {
  command_line->AppendSwitch("disable-spell-checking");
  command_line->AppendSwitch("disable-extensions");
  command_line->AppendSwitch("disable-web-security");
  command_line->AppendSwitch("disable-pdf-extension");
  command_line->AppendSwitch("enable-direct-write");
  command_line->AppendSwitch("allow-file-access-from-files");
  command_line->AppendSwitch("no-proxy-server");
  command_line->AppendSwitch("in-process-gpu");
  command_line->AppendSwitch("disable-direct-composition");
  command_line->AppendSwitchWithValue("disable-features", "NetworkService");
  command_line->AppendSwitchWithValue("renderer-process-limit", "1");
  command_line->AppendSwitchWithValue("disable-usb-keyboard-detect", "1");
}

void QCefViewBrowserApp::OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) {
  // register custom shcemes
  RegisterCustomSchemes(registrar);
}

CefRefPtr<CefResourceBundleHandler> QCefViewBrowserApp::GetResourceBundleHandler() {
  return nullptr;
}

CefRefPtr<CefBrowserProcessHandler>
QCefViewBrowserApp::GetBrowserProcessHandler() {
  return this;
}

CefRefPtr<CefRenderProcessHandler> QCefViewBrowserApp::GetRenderProcessHandler() {
  return nullptr;
}

void QCefViewBrowserApp::OnContextInitialized() {
  CEF_REQUIRE_UI_THREAD();

  // create all browser delegates
  CreateDelegates(browser_delegates_);

  RegisterCustomSchemesHandlerFactories();

  DelegateSet::iterator it = browser_delegates_.begin();
  for (; it != browser_delegates_.end(); ++it)
    (*it)->OnContextInitialized(this);
}

void QCefViewBrowserApp::OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line) {
  if (bridge_object_name_.empty())
    bridge_object_name_ = QCEF_OBJECT_NAME;

  command_line->AppendSwitchWithValue(QCEF_BRIDGE_OBJ_NAME_KEY, bridge_object_name_);
  DelegateSet::iterator it = browser_delegates_.begin();
  for (; it != browser_delegates_.end(); ++it)
    (*it)->OnBeforeChildProcessLaunch(this, command_line);
}

void QCefViewBrowserApp::OnScheduleMessagePumpWork(int64 delay_ms) {}

}