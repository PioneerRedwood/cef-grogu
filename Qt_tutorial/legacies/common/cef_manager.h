#pragma once

#include <mutex>

#include <QObject>
#include <QWidget>
#include <QThread>
#include <QCoreApplication>

#include "qcview/browser/browser_app.h"

namespace qcview {
class CefManager : public QObject {
  Q_OBJECT

protected:
  CefManager();
  ~CefManager(){};

public:
  static CefManager& getInstance();
  void initializeCef();
  bool addCookie(const std::string& name, const std::string& value, const std::string& domain, const std::string& url);
  void uninitializeCef();

protected slots:
  void releaseCef();

private:
  CefRefPtr<QCefViewBrowserApp> app_;
  CefSettings cef_settings_;
  int64_t browser_ref_count_;
};

} // namespace qcview