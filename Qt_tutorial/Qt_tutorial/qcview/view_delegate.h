#ifndef VIEW_DELEGATE_H
#define VIEW_DELEGATE_H

#include <vector>

#include "cef_binary_win64/include/internal/cef_win.h"
#include "cef_binary_win64/include/cef_values.h"

// changing this to QCViewImpl

class QCViewDelegate {
public:
    virtual ~QCViewDelegate();
    virtual void SetCefBrowserWindow(CefWindowHandle hwnd) = 0;
    virtual void OnLoadingStateChanged(bool isLoading,
                                       bool canGoBack,
                                       bool canGoForward) = 0;
    virtual void OnLoadStart() = 0;
    virtual void OnLoadEnd(int httpStatusCode) = 0;

    virtual void OnDraggableRegionChanged(
            const std::vector<CefDraggableRegion> regions) = 0;
    virtual void OnConsoleMessage(const CefString& message, int level) = 0;

    virtual void OnTakeFocus(bool next) = 0;

    virtual void OnUrlRequest(const CefString& url) = 0;
    virtual void OnQueryRequest(const CefString& request, int64 query_id) = 0;
    virtual void OnInvokeNotify(int browserId,
                                const CefRefPtr<CefListValue>& arguments) = 0;
};


#endif // VIEW_DELEGATE_H
