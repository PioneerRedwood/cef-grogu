#ifndef VIEW_IMPL_H
#define VIEW_IMPL_H
#pragma once

#include <QVBoxLayout>
#include <QWindow>
#include <QResizeEvent>
#include <QVariant>

#include <include/cef_app.h>
#include <include/cef_browser.h>
#include <include/cef_frame.h>
#include <include/cef_parser.h>
#include <include/cef_sandbox_win.h>

#include "QtCefView/browser_handler.h"

namespace qcview {
class QCViewImpl {
public:
    explicit QCViewImpl(const QString& url, QCView* view)
        : {

    }

private:
    QPointer<CefWindow> cef_window_;
    CefRefPtr<QCViewBrowserHandler
};


}

#endif // VIEW_IMPL_H
