#ifndef BROWSER_HANDLER_H
#define BROWSER_HANDLER_H

#include <list>
#include <map>
#include <set>
#include <string>
#include <mutex>

#include "include/cef_client.h"
#include "include/wrapper/cef_message_router.h"
#include "include/wrapper/cef_resource_manager.h"

#include "QtCefView/window.h"
#include "QtCefView/query_handler.h"
#include "QtCefView/view.h"

namespace qcview {
class QCHandler
        : public CefClient,
        public CefContextMenuHandler,
        public CefLifeSpanHandler,
        public CefLoadHandler,
        public CefRequestHandler,
        public CefResourceRequestHandler {
public:
    // Implement this interface to receive notification of QCHandler
    // events.
    class Delegate {
    public:
        virtual ~Delegate();
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

public:
    QCHandler(QCViewDelegate *delegate);
    ~QCHandler();

  // CefClient methods:
  CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() override { return this; }
  CefRefPtr<CefDisplayHandler> GetDisplayHandler() override { return this; }
  CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
  CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }
  CefRefPtr<CefRequestHandler> GetRequestHandler() override { return this; }
  bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame,
                                CefProcessId source_process,
                                CefRefPtr<CefProcessMessage> message) override;

  // CefContextMenuHandler methods
  void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefFrame> frame,
                                   CefRefPtr<CefContextMenuParams> params,
                           CefRefPtr<CefMenuModel> model) override;
  bool OnContextMenuCommand(CefRefPtr<CefBrowser> browser,
                                    CefRefPtr<CefFrame> frame,
                                    CefRefPtr<CefContextMenuParams> params,
                                    int command_id,
                            EventFlags event_flags) override ;

  // CefDisplayHandler methods
  void OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString &url) override;
  void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString &title) override;
  bool OnConsoleMessage(CefRefPtr<CefBrowser> browser,
                        cef_log_severity_t level,
                        const CefString &message,
                        const CefString &source,
                        int line) override;

  // CefLifeSpanHandler methods:
  bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
                             CefRefPtr<CefFrame> frame,
                             const CefString &target_url,
                             const CefString &target_frame_name,
                             CefLifeSpanHandler::WindowOpenDisposition target_disposition,
                             bool user_gesture,
                             const CefPopupFeatures &popupFeatures,
                             CefWindowInfo &windowInfo,
                             CefRefPtr &client,
                             CefBrowserSettings &settings,
                             CefRefPtr &extra_info,
                             bool *no_javascript_access) override;
  void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
  bool DoClose(CefRefPtr<CefBrowser> browser) override;
  void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

  // CefLoadHandler methods
  void OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
                                    bool isLoading,
                                    bool canGoBack,
                                    bool canGoForward) override;
  void OnLoadStart(CefRefPtr<CefBrowser> browser,
                   CefRefPtr<CefFrame> frame,
                   TransitionType transition_type) override;
  void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) override;
  void OnLoadError(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           ErrorCode errorCode,
                           const CefString &errorText,
                           const CefString &failedUrl) override;

  // CefRequestHandler methods
  bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
                              CefRefPtr<CefFrame> frame,
                              CefRefPtr<CefRequest> request,
                              bool user_gesture,
                              bool is_redirect) override;

  bool OnOpenURLFromTab(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame,
                                const CefString &target_url,
                                CefRequestHandler::WindowOpenDisposition target_disposition,
                                bool user_gesture) override;
  CefRefPtr<CefResourceRequestHandler> GetResourceRequestHandler(CefRefPtr<CefBrowser> browser,
                                                                         CefRefPtr<CefFrame> frame,
                                                                         CefRefPtr<CefRequest> request,
                                                                         bool is_navigation,
                                                                         bool is_download,
                                                                         const CefString &request_initiator,
                                                                         bool &disable_default_handling) override;
  bool OnQuotaRequest(CefRefPtr<CefBrowser> browser,
                              const CefString &origin_url,
                              int64 new_size,
                              CefRefPtr<CefCallback> callback) override;

  void OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser, TerminationStatus status) override;

  // CefResourceRequestHandler methods
  ReturnValue OnBeforeResourceLoad(CefRefPtr<CefBrowser> browser,
                                           CefRefPtr<CefFrame> frame,
                                           CefRefPtr<CefRequest> request,
                                           CefRefPtr<CefCallback> callback) override;
  CefRefPtr<CefResourceHandler> GetResourceHandler(CefRefPtr<CefBrowser> browser,
                                                           CefRefPtr<CefFrame> frame,
                                                           CefRefPtr<CefRequest> request) override;
  void OnProtocolExecution(CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefFrame> frame,
                                   CefRefPtr<CefRequest> request,
                                   bool &allow_os_execution) override;


  CefRefPtr<CefBrowser> GetBrowser() const;
  void AddLocalDirectoryResourceProvider(const std::string &dir_path, const std::string &url, int priority = 0);
  void AddArchiveResourceProvider(const std::string &archive_path,
                                  const std::string &url,
                                  const std::string &password,
                                  int priority = 0);

  // Request that all existing browser windows close.
  void CloseAllBrowsers(bool force_close);
  bool TriggerEvent(const int64_t frame_id, const CefRefPtr<CefProcessMessage> msg);
  bool ResponseQuery(const int64_t query, bool success, const CefString &response, int error);
//  bool DispatchNotifyRequest(CefRefPtr<CefBrowser> browser,
//                             CefProcessId source_process,
//                             CefRefPtr<CefProcessMessage> message);
//  void NotifyTakeFocus(bool next);
//  void NotifyDragRegion(const std::vector<CefDraggableRegion> regions);

//  void SetContextMenuHandler(CefRefPtr<CefContextMenuHandler> handler) { context_menu_handler_ = handler; }
//  void SetDisplayHandler(CefRefPtr<CefDisplayHandler> handler) { display_handler_ = handler; }

private:
  Delegate *delegate_;
  int browser_count_;
  bool is_closing_;
  bool initial_navigation_;

  mutable std::mutex mtx_;
  mutable std::condition_variable close_cv_;
  CefRefPtr<CefBrowser> main_browser_;

  CefRefPtr<CefResourceManager> resource_manager_;
  CefRefPtr<CefMessageRouterBrowserSide> message_router_;
  CefRefPtr<QCQueryHandler> query_handler_;

  DISALLOW_COPY_AND_ASSIGN(QCHandler);
}
} // namespace qcview

#endif // BROWSER_HANDLER_H
