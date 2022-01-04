#include <include/cef_sandbox_win.h>

#include "qcview/browser/cef_manager.h"
#include "qcview/browser/cef_setting.h"

namespace qcview {
CefManager::CefManager() {
  browser_ref_count_ = 0;
}

CefManager& CefManager::getInstance() {
  static CefManager s_instance;
  return s_instance;
}

void CefManager::initializeCef() {
  // This is not the first time initialization
  if (++browser_ref_count_ > 1)
    return;

  // Enable High-DPI support on Windows 7 or newer.
  CefEnableHighDPISupport();

  // This is the first time initialization
  CefSetting::initializeInstance();

  CefString(&cef_settings_.browser_subprocess_path) = CefSetting::browser_sub_process_path;
  CefString(&cef_settings_.resources_dir_path) = CefSetting::resource_directory_path;
  CefString(&cef_settings_.locales_dir_path) = CefSetting::locales_directory_path;
  CefString(&cef_settings_.user_agent) = CefSetting::user_agent;
  CefString(&cef_settings_.cache_path) = CefSetting::cache_path;
  CefString(&cef_settings_.user_data_path) = CefSetting::user_data_path;
  CefString(&cef_settings_.locale) = CefSetting::locale;
  CefString(&cef_settings_.accept_language_list) = CefSetting::accept_language_list;

  cef_settings_.persist_session_cookies = CefSetting::persist_session_cookies;
  cef_settings_.persist_user_preferences = CefSetting::persist_user_preferences;
  cef_settings_.remote_debugging_port = CefSetting::remote_debugging_port;
  cef_settings_.background_color = CefSetting::background_color;
  cef_settings_.no_sandbox = true;
  cef_settings_.pack_loading_disabled = false;
  cef_settings_.multi_threaded_message_loop = true;

#ifndef NDEBUG
  cef_settings_.log_severity = LOGSEVERITY_DEFAULT;
  cef_settings_.remote_debugging_port = CefSetting::remote_debugging_port;
#else
  cef_settings_.log_severity = LOGSEVERITY_DISABLE;
#endif

  app_ = new QCefViewBrowserApp(CefSetting::bridge_object_name);

  HINSTANCE hInstance = ::GetModuleHandle(nullptr);
  CefMainArgs main_args(hInstance);

  // Initialize CEF.
  void* sandboxInfo = nullptr;
  if (!CefInitialize(main_args, cef_settings_, app_, sandboxInfo)) {
    assert(0);
  }
}

bool CefManager::addCookie(const std::string& name,
                       const std::string& value,
                       const std::string& domain,
                       const std::string& url) {
  CefCookie cookie;
  CefString(&cookie.name).FromString(name);
  CefString(&cookie.value).FromString(value);
  CefString(&cookie.domain).FromString(domain);
  return CefCookieManager::GetGlobalManager(nullptr)->SetCookie(CefString(url), cookie, nullptr);
}

void CefManager::uninitializeCef() {
  // This is not the last time release
  if (--browser_ref_count_ > 0) {
    return;
  }

  // Destroy the application
  app_ = nullptr;

  // The last time release
  // TO-DO (sheen) when we reach here, it is possible there are pending
  // IO requests, and they will fire the DCHECK when complete or aborted
  releaseCef();
}

void CefManager::releaseCef() {
  CefShutdown();
}

} // namespace qcview
