#pragma once

#include <vector>
#include <map>
#include <mutex>

#include <include/cef_base.h>
#include <include/cef_browser.h>
#include <include/cef_scheme.h>

#include "qcview/common/protocol.h"
#include "qcview/browser/view.h"

namespace qcview {
static char* scheme_name = QCEF_SCHEMA;

class SchemeHandler : public CefResourceHandler
{
public:
  SchemeHandler(QCefView::Delegate* pDelegate);
  bool Open(CefRefPtr<CefRequest> request, bool& handle_request, CefRefPtr<CefCallback> callback) override;
  bool ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefCallback> callback) override;
  void GetResponseHeaders(CefRefPtr<CefResponse> response,
                                  int64& response_length,
                                  CefString& redirectUrl) override;
  bool Skip(int64 bytes_to_skip, int64& bytes_skipped, CefRefPtr<CefResourceSkipCallback> callback) override;
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
  QCefView::Delegate* pQCefViewDelegate_;
  std::string data_;
  std::string mime_type_;
  int offset_;

private:
  IMPLEMENT_REFCOUNTING(SchemeHandler);
};

class SchemeHandlerFactory : public CefSchemeHandlerFactory
{
public:
  static void recordBrowserAndDelegate(CefRefPtr<CefBrowser> browser, QCefView::Delegate* pDelegate);
  static void removeBrowserAndDelegate(CefRefPtr<CefBrowser> browser);

  // Return a new scheme handler instance to handle the request.
  CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser,
                                      CefRefPtr<CefFrame> frame,
                                      const CefString& scheme_name,
                                      CefRefPtr<CefRequest> request) override;

private:
  static std::map<void*, QCefView::Delegate*> mapBrowser2Delegate_;
  static std::mutex mtxMap_;

private:
  IMPLEMENT_REFCOUNTING(SchemeHandlerFactory);
};


}