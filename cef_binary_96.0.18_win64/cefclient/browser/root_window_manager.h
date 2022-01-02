// Copyright (c) 2015 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_TESTS_CEFCLIENT_BROWSER_ROOT_WINDOW_MANAGER_H_
#define CEF_TESTS_CEFCLIENT_BROWSER_ROOT_WINDOW_MANAGER_H_
#pragma once

#include <memory>
#include <set>

#include "include/cef_command_line.h"
#include "include/cef_request_context_handler.h"
#include "cefclient/browser/root_window.h"
#include "cefclient/browser/temp_window.h"

namespace client {

class RootWindowManager : public RootWindow::Delegate {
 public:
  explicit RootWindowManager(bool terminate_when_all_windows_closed);

  scoped_refptr<RootWindow> CreateRootWindow(
      std::unique_ptr<RootWindowConfig> config);

  scoped_refptr<RootWindow> CreateRootWindowAsPopup(
      bool with_controls,
      bool with_osr,
      const CefPopupFeatures& popupFeatures,
      CefWindowInfo& windowInfo,
      CefRefPtr<CefClient>& client,
      CefBrowserSettings& settings);

  scoped_refptr<RootWindow> CreateRootWindowAsExtension(
      CefRefPtr<CefExtension> extension,
      const CefRect& source_bounds,
      CefRefPtr<CefWindow> parent_window,
      base::OnceClosure close_callback,
      bool with_controls,
      bool with_osr);

  bool HasRootWindowAsExtension(CefRefPtr<CefExtension> extension);

  scoped_refptr<RootWindow> GetWindowForBrowser(int browser_id) const;

  scoped_refptr<RootWindow> GetActiveRootWindow() const;

  CefRefPtr<CefBrowser> GetActiveBrowser() const;

  void CloseAllWindows(bool force);

  void AddExtension(CefRefPtr<CefExtension> extension);

  bool request_context_per_browser() const {
    return request_context_per_browser_;
  }

 private:
  friend std::default_delete<RootWindowManager>;

  ~RootWindowManager();

  void OnRootWindowCreated(scoped_refptr<RootWindow> root_window);
  void NotifyExtensionsChanged();

  // RootWindow::Delegate methods.
  CefRefPtr<CefRequestContext> GetRequestContext(
      RootWindow* root_window) override;
  //scoped_refptr<ImageCache> GetImageCache() override;
  void OnTest(RootWindow* root_window, int test_id) override;
  void OnExit(RootWindow* root_window) override;
  void OnRootWindowDestroyed(RootWindow* root_window) override;
  void OnRootWindowActivated(RootWindow* root_window) override;
  void OnBrowserCreated(RootWindow* root_window,
                        CefRefPtr<CefBrowser> browser) override;
  void CreateExtensionWindow(CefRefPtr<CefExtension> extension,
                             const CefRect& source_bounds,
                             CefRefPtr<CefWindow> parent_window,
                             base::OnceClosure close_callback,
                             bool with_osr) override;
  // RootWindow::Delegate::OnCallGrogu
  void OnCallGrogu(RootWindow* root_window, int test_id) override;

  void CleanupOnUIThread();

  const bool terminate_when_all_windows_closed_;
  bool request_context_per_browser_;
  bool request_context_shared_cache_;

  // Existing root windows. Only accessed on the main thread.
  typedef std::set<scoped_refptr<RootWindow>> RootWindowSet;
  RootWindowSet root_windows_;

  // The currently active/foreground RootWindow. Only accessed on the main
  // thread.
  scoped_refptr<RootWindow> active_root_window_;

  // The currently active/foreground browser. Access is protected by
  // |active_browser_lock_;
  mutable base::Lock active_browser_lock_;
  CefRefPtr<CefBrowser> active_browser_;

  // Singleton window used as the temporary parent for popup browsers.
  std::unique_ptr<TempWindow> temp_window_;

  CefRefPtr<CefRequestContext> shared_request_context_;

  // Loaded extensions. Only accessed on the main thread.
  ExtensionSet extensions_;

  //scoped_refptr<ImageCache> image_cache_;

  DISALLOW_COPY_AND_ASSIGN(RootWindowManager);
};

}  // namespace client

#endif  // CEF_TESTS_CEFCLIENT_BROWSER_ROOT_WINDOW_MANAGER_H_
