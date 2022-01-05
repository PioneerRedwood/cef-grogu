#ifndef QUERY_HANDLER_H
#define QUERY_HANDLER_H
#pragma once

#include <map>
#include <mutex>

#include "include/cef_base.h"
#include "include/wrapper/cef_stream_resource_handler.h"
#include "include/wrapper/cef_message_router.h"

#include "qcview/view.h"
#include "qcview/view_delegate.h"

class QCQueryHandler : public CefBaseRefCounted, public CefMessageRouterBrowserSide::Handler {
public:
    QCQueryHandler(QCViewDelegate* delegate);
    ~QCQueryHandler();

    bool OnQuery(CefRefPtr<CefBrowser> browser,
                 CefRefPtr<CefFrame> frame,
                 int64 query_id,
                 const CefString& request,
                 bool persistant,
                 CefRefPtr<Callback> callback) override;
    void OnQueryCanceled(CefRefPtr<CefBrowser> browser,
                         CefRefPtr<CefFrame> frame,
                         int64 query_id) override;

    bool Response(int64_t query,
                  bool success,
                  const CefString& response,
                  int error);
private:
    QCViewDelegate* delegate_;
    std::map<int64, CefRefPtr<Callback>> callback_map_;
    std::mutex mtx_;
private:
    IMPLEMENT_REFCOUNTING(QCQueryHandler);
};


#endif // QUERY_HANDLER_H
