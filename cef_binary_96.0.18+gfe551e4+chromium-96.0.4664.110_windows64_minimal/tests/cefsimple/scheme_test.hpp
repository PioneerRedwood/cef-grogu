#pragma once

#include <algorithm>
#include <string>

#include "include/cef_browser.h"
#include "include/cef_callback.h"
#include "include/cef_frame.h"
#include "include/cef_request.h"
#include "include/cef_resource_handler.h"
#include "include/cef_response.h"
#include "include/cef_scheme.h"
#include "include/wrapper/cef_helpers.h"
//#include "tests/cefclient/browser/test_runner.h"
#include "tests/shared/browser/resource_util.h"


namespace {
class SimpleSchemeHandler : public CefResourceHandler
{
public:
	SimpleSchemeHandler() : offset_(0) {}

	bool Open(CefRefPtr<CefRequest> request,
		bool& handle_request,
		CefRefPtr<CefCallback> callback) override 
	{
		// ?
	}

	void GetResponseHeaders(CefRefPtr<CefResponse> response,
		int64& response_length,
		CefString& redirectUrl) override 
	{
		// ?
	}

	void Cancel() override { CEF_REQUIRE_IO_THREAD(); }

	bool Read(void* data_out,
		int bytes_to_read,
		int& bytes_read,
		CefRefPtr<CefResourceReadCallback> callback) override 
	{
		// ?
	}

private:
	std::string data_;
	std::string mime_type_;
	std::size_t offset_;

	IMPLEMENT_REFCOUNTING(SimpleSchemeHandler);
	DISALLOW_COPY_AND_ASSIGN(SimpleSchemeHandler);
};

class SimpleSchemeHandlerFactory : public CefSchemeHandlerFactory {

public:
	SimpleSchemeHandlerFactory() {}

	CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& scheme_name,
		CefRefPtr<CefRequest> request) override 
	{
		CEF_REQUIRE_IO_THREAD();
		return new SimpleSchemeHandler();
	}

	IMPLEMENT_REFCOUNTING(SimpleSchemeHandlerFactory);
	DISALLOW_COPY_AND_ASSIGN(SimpleSchemeHandlerFactory);
};
}

void RegisterSchemeHandlers()
{
	CefRegisterSchemeHandlerFactory("client", "tests",
		new SimpleSchemeHandlerFactory());

}