#pragma once

#include <QWindow>
#include <QPointer>
#include <QVariant>
#include <QHash>
#include <QMutex>
#include <QRegion>

#include <include/cef_app.h>

#include "qcview/common/protocol.h"
#include "qcview/browser/view.h"
#include "qcview/browser/query.h"

namespace qcview {

class CefWindow
  : public QWindow
  , public QCefView::Delegate
{
  Q_OBJECT

public:
  explicit CefWindow(QCefView* view = 0);

  ~CefWindow();

  virtual void setCefBrowserWindow(CefWindowHandle hwnd) override;
  virtual void onLoadingStateChanged(bool isLoading, bool canGoBack, bool canGoForward) override;
  virtual void onLoadStart() override;
  virtual void onLoadEnd(int httpStatusCode) override;
  virtual void onLoadError(int errorCode,
                           const CefString& errorMsg,
                           const CefString& failedUrl,
                           bool& handled) override;
  virtual void onDraggableRegionChanged(const std::vector<CefDraggableRegion> regions) override;
  virtual void onConsoleMessage(const CefString& message, int level) override;
  virtual void onTakeFocus(bool next) override;
  virtual void onQCefUrlRequest(const CefString& url) override;
  virtual void onQCefQueryRequest(const CefString& request, int64 query_id) override;
  virtual void onInvokeMethodNotify(int browserId, const CefRefPtr<CefListValue>& arguments) override;

public:
  void syncCefBrowserWindow();
  virtual void exposeEvent(QExposeEvent* e);
  virtual void resizeEvent(QResizeEvent* e);

private:
  QCefView* view_;

  CefWindowHandle hwndCefBrowser_;
};
} // namespace qcview

