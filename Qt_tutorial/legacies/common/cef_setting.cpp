#include <QCoreApplication>
#include <QDir>

#include "qcview/common/protocol.h"
#include "qcview/common/cef_setting.h"

namespace qcview {
CefString CefSetting::bridge_object_name;

CefString CefSetting::browser_sub_process_path;

CefString CefSetting::resource_directory_path;

CefString CefSetting::locales_directory_path;

CefString CefSetting::user_agent;

CefString CefSetting::cache_path;

CefString CefSetting::user_data_path;

int CefSetting::persist_session_cookies;

int CefSetting::persist_user_preferences;

CefString CefSetting::locale;

int CefSetting::remote_debugging_port;

cef_color_t CefSetting::background_color;

CefString CefSetting::accept_language_list;

std::list<CefSetting::CookieItem> CefSetting::global_cookie_list;

void CefSetting::initializeInstance() {
  static CefSetting s_instance;
}

CefSetting::CefSetting() {
  QDir ExeDir = qApp->applicationDirPath();

  QString strExePath = ExeDir.filePath(RENDER_PROCESS_NAME);
  browser_sub_process_path.FromString(QDir::toNativeSeparators(strExePath).toStdString());

  QString strResPath = ExeDir.filePath(RESOURCE_DIRECTORY_NAME);
  resource_directory_path.FromString(QDir::toNativeSeparators(strResPath).toStdString());

  QDir ResPath(strResPath);
  locales_directory_path.FromString(QDir::toNativeSeparators(ResPath.filePath(LOCALES_DIRECTORY_NAME)).toStdString());

  user_agent.FromString(QCEF_USER_AGENT);
}

} // namespace qcview
