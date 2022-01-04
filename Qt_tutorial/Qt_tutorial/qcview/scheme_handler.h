#ifndef SCHEME_HANDLER_H
#define SCHEME_HANDLER_H
#pragma once

#include <vector>
#include <map>
#include <mutex>

#include "include/cef_base.h"
#include "include/cef_browser.h"
#include "include/cef_scheme.h"

#include "QtCefView/protocol.h"
#include "QtCefView/view.h"

namespace qcview {
class SchemeHandler : public CefResourceHandler {
public:
    SchemeHandler(QCHandler::Delegate* delegate);
    bool Open(CefRefPtr<CefRequest> request,
              bool& handle_request,
              CefRefPtr<CefCallback> callback) override {
        handle_request = false;
        // if(delegate_) {
        if(true) {
            CefString cefStrUrl = request->GetURL();
            // delegate_->OnUrlRequest(cefStrUrl);
        }

        return false;
    }
    bool ProcessRequest(CefRefPtr<CefRequest> request,
                                CefRefPtr<CefCallback> callback) override {
        // if(delegate_) {
        CefString url = request->GetURL();
        delegate_->
    }

    void GetResponseHeaders(CefRefPtr<CefResponse> response,
                                    int64& response_length,
                                    CefString& redirectUrl) override;

    bool Skip(int64 bytes_to_skip,
                      int64& bytes_skipped,
                      CefRefPtr<CefResourceSkipCallback> callback) override;

    bool Read(void* data_out,
              int bytes_to_read,
              int& bytes_read,
              CefRefPtr<CefResourceReadCallback> callback) override;

    bool ReadResponse(void* data_out,
                      int bytes_to_read,
                      int& bytes_read,
                      CefRefPtr<CefCallback> callback) override;

    void Cancel() override;
private:
    QCView::Delegate* delegate_;
    std::string data_;
    std::string mime_type_;
    int offset_;
private:
    IMPLEMENT_REFCOUNTING(SchemeHandler);
};
}

#endif // SCHEME_HANDLER_H
