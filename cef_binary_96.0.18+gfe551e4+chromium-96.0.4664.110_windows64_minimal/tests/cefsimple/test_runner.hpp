// Copyright (c) 2015 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_TESTS_CEFCLIENT_BROWSER_TEST_RUNNER_H_
#define CEF_TESTS_CEFCLIENT_BROWSER_TEST_RUNNER_H_
#pragma once

#include <set>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <sstream>

#include "include/cef_browser.h"
#include "include/cef_request.h"
#include "include/wrapper/cef_message_router.h"
#include "include/wrapper/cef_resource_manager.h"

#include "include/base/cef_callback.h"
#include "include/cef_parser.h"
#include "include/cef_task.h"
#include "include/cef_trace.h"
#include "include/cef_web_plugin.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_stream_resource_handler.h"

//#include "tests/cefclient/browser/binding_test.h"
//#include "tests/cefclient/browser/client_handler.h"
//#include "tests/cefclient/browser/dialog_test.h"
#include "tests/cefclient/browser/main_context.h"
//#include "tests/cefclient/browser/media_router_test.h"
//#include "tests/cefclient/browser/preferences_test.h"
#include "tests/cefclient/browser/resource.h"
//#include "tests/cefclient/browser/response_filter_test.h"
#include "tests/cefclient/browser/root_window_manager.h"
#include "tests/cefclient/browser/scheme_test.h"
#include "tests/cefclient/browser/server_test.h"
//#include "tests/cefclient/browser/urlrequest_test.h"
//#include "tests/cefclient/browser/window_test.h"
#include "tests/shared/browser/resource_util.h"

namespace client {
namespace test_runner {

namespace {

const char kTestHost[] = "tests";
const char kLocalHost[] = "localhost";
const char kTestOrigin[] = "http://tests/";

const char kTestGetSourcePage[] = "get_source.html";
const char kTestGetTextPage[] = "get_text.html";
const char kTestPluginInfoPage[] = "plugin_info.html";

// Set page data and navigate the browser. Used in combination with
// StringResourceProvider.
void LoadStringResourcePage(CefRefPtr<CefBrowser> browser,
    const std::string& page,
    const std::string& data) {
    CefRefPtr<CefClient> client = browser->GetHost()->GetClient();
    //ClientHandler* client_handler = static_cast<ClientHandler*>(client.get());
    SimpleHandler* client_handler = static_cast<ClientHandler*>(client.get());
    client_handler->SetStringResource(page, data);
    browser->GetMainFrame()->LoadURL(kTestOrigin + page);
}

// Replace all instances of |from| with |to| in |str|.
std::string StringReplace(const std::string& str,
    const std::string& from,
    const std::string& to) {
    std::string result = str;
    std::string::size_type pos = 0;
    std::string::size_type from_len = from.length();
    std::string::size_type to_len = to.length();
    do {
        pos = result.find(from, pos);
        if (pos != std::string::npos) {
            result.replace(pos, from_len, to);
            pos += to_len;
        }
    } while (pos != std::string::npos);
    return result;
}


}

// Run a test.
void RunTest(CefRefPtr<CefBrowser> browser, int id)
{
    if (!browser)
    {
        return;
    }

    switch (id)
    {
    
    }
}

// Returns the contents of the CefRequest as a string.
std::string DumpRequestContents(CefRefPtr<CefRequest> request)
{

}

// Returns the dump response as a stream. |request| is the request.
// |response_headers| will be populated with extra response headers, if any.
CefRefPtr<CefStreamReader> GetDumpResponse(
    CefRefPtr<CefRequest> request,
    CefResponse::HeaderMap& response_headers)
{

}

// Returns a data: URI with the specified contents.
std::string GetDataURI(const std::string& data, const std::string& mime_type)
{

}

// Returns the string representation of the specified error code.
std::string GetErrorString(cef_errorcode_t code)
{

}

using StringResourceMap = std::map<std::string, std::string>;

// Set up the resource manager for tests.
void SetupResourceManager(CefRefPtr<CefResourceManager> resource_manager,
    StringResourceMap* string_resource_map)
{

}

// Show a JS alert message.
void Alert(CefRefPtr<CefBrowser> browser, const std::string& message)
{

}

// Returns true if |url| is a test URL with the specified |path|. This matches
// both http://tests/<path> and http://localhost:xxxx/<path>.
bool IsTestURL(const std::string& url, const std::string& path)
{

}

// Create all CefMessageRouterBrowserSide::Handler objects. They will be
// deleted when the ClientHandler is destroyed.
using MessageHandlerSet = std::set<CefMessageRouterBrowserSide::Handler*>;
void CreateMessageHandlers(MessageHandlerSet& handlers)
{

}

// Register scheme handlers for tests.
void RegisterSchemeHandlers()
{

}

// Create a resource response filter for tests.
CefRefPtr<CefResponseFilter> GetResourceResponseFilter(
    CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    CefRefPtr<CefRequest> request,
    CefRefPtr<CefResponse> response)
{

}

}  // namespace test_runner
}  // namespace client

#endif  // CEF_TESTS_CEFCLIENT_BROWSER_TEST_RUNNER_H_
