#pragma once

#include <include\cef_base.h>

namespace qcview {

class CefSetting
{
protected:
  CefSetting();
  ~CefSetting(){};

public:
  static void initializeInstance();

public:
  static CefString bridge_object_name;
  static CefString browser_sub_process_path;
  static CefString resource_directory_path;
  static CefString locales_directory_path;
  static CefString user_agent;
  static CefString cache_path;
  static CefString user_data_path;
  static int persist_session_cookies;
  static int persist_user_preferences;
  static CefString locale;
  static int remote_debugging_port;
  static cef_color_t background_color;
  static CefString accept_language_list;
  typedef struct CookieItem
  {
    std::string name;
    std::string value;
    std::string domain;
    std::string url;
  } CookieItem;
  static std::list<CookieItem> global_cookie_list;
};

} // namespace qcview
