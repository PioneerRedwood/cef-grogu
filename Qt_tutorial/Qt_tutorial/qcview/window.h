#ifndef CEF_WINDOW_H
#define CEF_WINDOW_H
#pragma once

#include <vector>

#include "QWindow"
#include "QPointer"
#include "QVariant"
#include "QHash"
#include "QMutex"
#include "QRegion"

#include "include/cef_app.h"

#include "qcview/view.h"
#include "qcview/view_delegate.h"
#include "qcview/handler.h"

class QCView;

class QCWindow :
        public QWindow,
        public QCViewDelegate {
    Q_OBJECT
public:
    QCWindow() {}
    ~QCWindow() {}

    // QCViewDelegate methods
    void SetCefBrowserWindow(CefWindowHandle hwnd) override {

    }
    void OnLoadingStateChanged(bool isLoading,
                               bool canGoBack,
                               bool canGoForward) override {

    }
    void OnLoadStart() override {

    }
    void OnLoadEnd(int httpStatusCode) override {

    }

    void OnDraggableRegionChanged(const std::vector<CefDraggableRegion> regions) override {

    }
    void OnConsoleMessage(const CefString& message, int level) override {

    }
    void OnTakeFocus(bool next) override {

    }
    void OnUrlRequest(const CefString& url) override {

    }
    void OnQueryRequest(const CefString& request, int64 query_id) override {

    }
    void OnInvokeNotify(int browserId, const CefRefPtr<CefListValue>& arguments) override  {

    }

public:
    void syncCefBrowserWindow();
    virtual void exposeEvent(QExposeEvent* event);
    virtual void resizeEvent(QResizeEvent* event);

private:
    std::shared_ptr<QCView> view_;
    CefWindowHandle hwnd_;
};


#endif // CEF_WINDOW_H
