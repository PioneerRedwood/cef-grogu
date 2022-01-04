#include "QtCefView/view.h"
#include "QtCefView/window.h"

namespace qcview {
CefWindow::CefWindow(QCView* view)
    :QWindow(view->windowHandle()),
      view_(view),
      hwnd_(nullptr){
    setFlags(Qt::FramelessWindowHint);

    // initializeCef here
}

CefWindow::~CefWindow() {
    if(hwnd_) {
        hwnd_ = nullptr;
    }

    // uninitializeCef here
}

void CefWindow::setCefBrowserWindow(CefWindowHandle hwnd) {
    hwnd_ = hwnd;
    syncCefBrowserWindow();
}

void CefWindow::onLoadingStateChanged(bool isLoading, bool canGoBack, bool canGoForward) {
    if(view_) {
        view_->onLoadingStateChanged(isLoading, canGoBack, canGoForward);
    }
}
}
