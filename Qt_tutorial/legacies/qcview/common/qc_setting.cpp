#pragma once

#include <QtCore/qglobal.h>
#include <QString>
#include <QMetaType>

#include "qcview/common/cef_setting.h"

#include <QColor.h>

#ifdef QCEFVIEW_LIB
#define QCEFVIEW_EXPORT Q_DECL_EXPORT
#else
#define QCEFVIEW_EXPORT Q_DECL_IMPORT
    #if _WIN32
    #pragma comment(lib, "QCefView.lib")
    #endif
#endif

namespace qcview {
    
void QCEFVIEW_EXPORT setBrowserSubProcessPath(const QString& path) {
  CefSetting::initializeInstance();
  CefSetting::browser_sub_process_path.FromString(path.toStdString());
}

const QCEFVIEW_EXPORT QString browserSubProcessPath() {
  CefSetting::initializeInstance();
  return QString::fromStdString(CefSetting::browser_sub_process_path.ToString());
}

void QCEFVIEW_EXPORT setResourceDirectoryPath(const QString& path) {
  CefSetting::initializeInstance();
  CefSetting::resource_directory_path.FromString(path.toStdString());
}

const QCEFVIEW_EXPORT QString resourceDirectoryPath() {
  CefSetting::initializeInstance();
  return QString::fromStdString(CefSetting::resource_directory_path.ToString());

}

void QCEFVIEW_EXPORT setLocalesDirectoryPath(const QString& path) {
  CefSetting::initializeInstance();
  CefSetting::locales_directory_path.FromString(path.toStdString());

}

const QCEFVIEW_EXPORT QString localesDirectoryPath() {
  CefSetting::initializeInstance();
  return QString::fromStdString(CefSetting::locales_directory_path.ToString());

}

void QCEFVIEW_EXPORT setUserAgent(const QString& agent) {
  CefSetting::initializeInstance();
  CefSetting::user_agent.FromString(agent.toStdString());

}

const QCEFVIEW_EXPORT QString userAgent() {
  CefSetting::initializeInstance();
  return QString::fromStdString(CefSetting::user_agent.ToString());

}

void QCEFVIEW_EXPORT setCachePath(const QString& path) {
  CefSetting::initializeInstance();
  CefSetting::cache_path.FromString(path.toStdString());

}

const QCEFVIEW_EXPORT QString cachePath() {
  CefSetting::initializeInstance();
  return QString::fromStdString(CefSetting::cache_path.ToString());

}

void QCEFVIEW_EXPORT setUserDataPath(const QString& path) {
  CefSetting::initializeInstance();
  CefSetting::user_data_path.FromString(path.toStdString());

}

const QCEFVIEW_EXPORT QString userDataPath() {
  CefSetting::initializeInstance();
  return QString::fromStdString(CefSetting::user_data_path.ToString());

}

void QCEFVIEW_EXPORT setBridgeObjectName(const QString& name) {
  CefSetting::initializeInstance();
  CefSetting::bridge_object_name.FromString(name.toStdString());

}

const QCEFVIEW_EXPORT QString bridgeObjectName() {
  CefSetting::initializeInstance();
  return QString::fromStdString(CefSetting::bridge_object_name);

}

void QCEFVIEW_EXPORT setPersistSessionCookies(bool enabled) {
  CefSetting::initializeInstance();
  CefSetting::persist_session_cookies = enabled ? TRUE : FALSE;

}

const QCEFVIEW_EXPORT bool persistSessionCookies() {
  CefSetting::initializeInstance();
  return CefSetting::persist_session_cookies ? true : false;

}

void QCEFVIEW_EXPORT setPersistUserPreferences(bool enabled) {
  CefSetting::initializeInstance();
  CefSetting::persist_user_preferences = enabled ? TRUE : FALSE;

}

const QCEFVIEW_EXPORT bool persistUserPreferences() {
  CefSetting::initializeInstance();
  return CefSetting::persist_user_preferences ? true : false;

}

void QCEFVIEW_EXPORT setLocale(const QString& locale) {
  CefSetting::initializeInstance();
  CefSetting::locale.FromString(locale.toStdString());

}

const QCEFVIEW_EXPORT QString locale() {
  CefSetting::initializeInstance();
  return QString::fromStdString(CefSetting::locale.ToString());

}

void QCEFVIEW_EXPORT setRemoteDebuggingPort(int port) {
  CefSetting::initializeInstance();
  CefSetting::remote_debugging_port = port;

}

const QCEFVIEW_EXPORT int remoteDebuggingPort() {
  CefSetting::initializeInstance();
  return CefSetting::remote_debugging_port;

}

void QCEFVIEW_EXPORT setBackgroundColor(const QColor& color) {
  CefSetting::initializeInstance();
  CefSetting::background_color = static_cast<cef_color_t>(color.rgba());
}

const QCEFVIEW_EXPORT QColor backgroundColor() {
  CefSetting::initializeInstance();
  return QColor::fromRgba(static_cast<QRgb>(CefSetting::background_color));
}

void QCEFVIEW_EXPORT setAcceptLanguageList(const QString& languages) {
  CefSetting::initializeInstance();
  CefSetting::accept_language_list.FromString(languages.toStdString());
}

const QCEFVIEW_EXPORT QString acceptLanguageList() {
  CefSetting::initializeInstance();
  return QString::fromStdString(CefSetting::accept_language_list.ToString());
}

void QCEFVIEW_EXPORT setGlobalCookie(
                                const QString& name, 
                                const QString& value, 
                                const QString& domain, 
                                const QString& url) {
    CefSetting::initializeInstance();
    CefSetting::global_cookie_list.push_back({
            name.toStdString(), value.toStdString(), domain.toStdString(), url.toStdString() 
        });
}

};