#pragma once

#include <memory>

#include <QtCore/qglobal.h>
#include <QWidget>
#include <QVariantList>

#include "qcview/browser/query.h"
#include "qcview/common/event.h"

#include <include/cef_client.h>

#ifdef QCEFVIEW_LIB
#define QCEFVIEW_EXPORT Q_DECL_EXPORT
#else
  #define QCEFVIEW_EXPORT Q_DECL_IMPORT
  #if _WIN32
    #pragma comment(lib, "QCefView.lib")
  #endif
#endif

/** Outline of QCefView:
 **
 **		+--------------------------------------------------------------+
 **		| QCefView(QWidget)                                            |
 **		|                                                              |
 **		|    +----------------------------------------------------+    |
 **		|    | WindowWrapper(QWidget)                             |    |
 **		|    |                                                    |    |
 **		|    |    +-------------------------------------------+   |    |
 **		|    |    | CefWindow(QWindow)                        |   |    |
 **		|    |    |                                           |   |    |
 **		|    |    |                                           |   |    |
 **		|    |    |                                           |   |    |
 **		|    |    +-------------------------------------------+   |    |
 **		|    |                                                    |    |
 **		|    +----------------------------------------------------+    |
 **		|                                                              |
 **		+--------------------------------------------------------------+
 **
 **	Remarks:
 **		The WindowWrapper and CefWindow are transparent to upper layer user.
 **
 **/

class CefContextMenuHandler;
class CefDialogHandler;
class CefDisplayHandler;
class CefDownloadHandler;
class CefJSDialogHandler;
class CefKeyboardHandler;

namespace qcview {
class QCEFVIEW_EXPORT QCefView : public QWidget {
  Q_OBJECT
public:
  class Delegate {
    public:
      virtual ~Delegate(){};
      virtual void setCefBrowserWindow(CefWindowHandle hwnd) = 0;
      virtual void onLoadingStateChanged(bool isLoading, bool canGoBack, bool canGoForward) = 0;
      virtual void onLoadStart() = 0;
      virtual void onLoadEnd(int httpStatusCode) = 0;
      virtual void onLoadError(int errorCode, const CefString& errorMsg, const CefString& failedUrl, bool& handled) = 0;
      virtual void onDraggableRegionChanged(const std::vector<CefDraggableRegion> regions) = 0;
      virtual void onConsoleMessage(const CefString& message, int level) = 0;
      virtual void onTakeFocus(bool next) = 0;
      virtual void onQCefUrlRequest(const CefString& url) = 0;
      virtual void onQCefQueryRequest(const CefString& request, int64 query_id) = 0;
      virtual void onInvokeMethodNotify(int browserId, const CefRefPtr<CefListValue>& arguments) = 0;
  };
public:
  QCefView(const QString url, QWidget* parent = 0);
  QCefView(QWidget* parent = 0);
  ~QCefView();
  static void addLocalFolderResource(const QString& path, const QString& url, int priority = 0);
  static void addArchiveResource(const QString& path, const QString& url, const QString& password = "");

  void addCookie(const QString& name, const QString& value, const QString& domain, const QString& url);

  WId getCefWinId();

  void navigateToString(const QString& content);
  void navigateToUrl(const QString& url);

  bool browserCanGoBack();
  bool browserCanGoForward();

  void browserGoBack();
  void browserGoForward();

  bool browserIsLoading();
  void browserReload();
  void browserStopLoad();

  bool triggerEvent(const QCefEvent& event);
  bool triggerEvent(const QCefEvent& event, int frameId);

  bool broadcastEvent(const QCefEvent& event);
  bool responseQCefQuery(const QCefQuery& query);

  void setContextMenuHandler(CefContextMenuHandler* handler);
  void setDialogHandler(CefDialogHandler* handler);
  void setDisplayHandler(CefDisplayHandler* handler);
  void setDownloadHandler(CefDownloadHandler* handler);
  void setJSDialogHandler(CefJSDialogHandler* handler);
  void setKeyboardHandler(CefKeyboardHandler* handler);

  virtual void onLoadingStateChanged(bool isLoading, bool canGoBack, bool canGoForward);
  virtual void onLoadStart();
  virtual void onLoadEnd(int httpStatusCode);
  virtual void onLoadError(int errorCode, const QString& errorMsg, const QString& failedUrl, bool& handled);
  virtual void onDraggableRegionChanged(const QRegion& region);
  virtual void onConsoleMessage(const QString& message, int level);
  virtual void onTakeFocus(bool next);
  virtual void onQCefUrlRequest(const QString& url);
  virtual void onQCefQueryRequest(const QCefQuery& query);
  virtual void onInvokeMethodNotify(int browserId, int frameId, const QString& method, const QVariantList& arguments);

protected:
  virtual void changeEvent(QEvent* event) override;
  virtual bool eventFilter(QObject* watched, QEvent* event) override;

private:
  class Implementation;
  std::unique_ptr<Implementation> pImpl_;
};

}