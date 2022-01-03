#pragma once

#include <set>
#include <include/cef_app.h>

#include "qcview/browser/scheme_handler.h"

namespace qcview {

// QCefViewBrowserApp for Qt + Cef
class QCefViewBrowserApp : public CefApp, public CefBrowserProcessHandler {
public:
  class Delegate : public virtual CefBaseRefCounted {
  public:
    virtual void OnContextInitialized(CefRefPtr<QCefViewBrowserApp> app) {}
    virtual void OnBeforeChildProcessLaunch(CefRefPtr<QCefViewBrowserApp> app, CefRefPtr<CefCommandLine> command_line) {}
  };
  // typedef std::set<CefRefPtr<Delegate>> DelegateSet;
  using DelegateSet = std::set<CefRefPtr<Delegate>>;

public:
  QCefViewBrowserApp(const CefString& name);
  ~QCefViewBrowserApp();

private:
  // CefApp methods:
  virtual void OnBeforeCommandLineProcessing(const CefString& process_type,
                                             CefRefPtr<CefCommandLine> command_line) override;
  virtual void OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) override;
  virtual CefRefPtr<CefResourceBundleHandler> GetResourceBundleHandler() override;
  virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;
  virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override;

  // CefBrowserProcessHandler methods:
  virtual void OnContextInitialized() override;
  virtual void OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line) override;
  virtual void OnScheduleMessagePumpWork(int64 delay_ms) override;

private:
  // Creates all of the Delegate objects. Implemented in
  // client_app_delegates.
  static void CreateDelegates(DelegateSet& delegates);

  // Rigster custom schemes handler factories
  static void RegisterCustomSchemesHandlerFactories();

  // Registers custom schemes. Implemented in client_app_delegates.
  static void RegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar);

private:
  CefString bridge_object_name_;

  // Set of supported Delegates. Only used in the browser process.
  DelegateSet browser_delegates_;

  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(QCefViewBrowserApp);
};

}
