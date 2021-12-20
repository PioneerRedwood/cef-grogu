// Copyright (c) 2016 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "tests/cefclient/browser/root_window.h"

#include "tests/cefclient/browser/root_window_views.h"

#include "tests/cefclient/browser/root_window_win.h"

namespace client {

// static
scoped_refptr<RootWindow> RootWindow::Create(bool use_views) {
  if (use_views) {
    return new RootWindowViews();
  }
  return new RootWindowWin();
}

}  // namespace client
