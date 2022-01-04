#ifndef CEF_WINDOW_H
#define CEF_WINDOW_H
#pragma once

#include "QWindow"
#include "QPointer"
#include "QVariant"
#include "QHash"
#include "QMutex"
#include "QRegion"

#include "include/cef_app.h"

#include "QtCefView/view.h"
#include "QtCefView/browser_handler.h"

namespace qcview {
class QCWindow : public QWindow, public QCHandler::Delegate {
    Q_OBJECT
public:
    explicit QCWindow(QCView* view = 0);
    ~QCWindow();
    // QCHandler::Delegate methods
    void SetCefBrowserWindow(CefWindowHandle hwnd) override;
    void OnLoadingStateChanged(bool isLoading,
                               bool canGoBack,
                               bool canGoForward) override;
    void OnLoadStart() override;
    void OnLoadError(int errorCode,
                     const CefString& errorMsg,
                     const CefString& failedUrl,
                     bool& handled) override;
    void OnDraggableRegionChanged(const std::vector<CefDraggableRegion> regions) override;
    void OnConsoleMessage(const CefString& message, int level) override;
    void OnTakeFocus(bool next) override;
    void OnUrlRequest(const CefString& url) override;
    void OnQueryRequest(const CefString& request, int64 query_id) override;
    void OnInvokeNotify(int browserId, const CefRefPtr<CefListValue>& arguments) override;

public:
    void syncCefBrowserWindow();
    // QWindow methods
    virtual void exposeEvent(QExposeEvent* event);
    virtual void resizeEvent(QResizeEvent* event);

private:
    QCView* view_;
    CefWindowHandle hwnd_;
};


}


#endif // CEF_WINDOW_H
