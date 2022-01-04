#ifndef QT_CEF_VIEW_H
#define QT_CEF_VIEW_H
#pragma once

#include <memory>

#include "QtCore/qglobal.h"
#include "QWidget"
#include "QVariantList"
#include "QVBoxLayout"
#include "QWindow"
#include "QResizeEvent"
#include "QVariant"

#include "include/cef_client.h"
#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_frame.h"
#include "include/cef_parser.h"

#include "QtCefView/browser_handler.h"
#include "QtCefView/protocol.h"
#include "QtCefView/window.h"

class CefContextMenuHandler;
class CefDisplayHandler;
class CefLifeSpanHandler;
class CefLoadHandler;

namespace qcview {

class QCView : public QWidget, public QCHandler::Delegate {
    Q_OBJECT
public:
    QCView(const QString& url, QWidget* parent = 0);
    QCView(QWidget* parent = 0);
    ~QCView();

    static void addLocalFolderResource(const QString& path,
                                       const QString& url,
                                       int priority = 0);

    static void addArchiveResource(const QString& path,
                                   const QString& url,
                                   const QString& password = 0);

    void addCookie(const QString& name,
                   const QString& value,
                   const QString& domain,
                   const QString& url);

    WId getCefWinId();

    void navigateToString(const QString& content);

    void navigateToUrl(const QString& url);

    bool browserIsLoading();

    bool browserReload();

    bool browserStopLoad();

    bool triggerEvent(const QCEvent& event);

    bool triggerEvent(const QCEvent& event, int frameId);

    bool broadcastEvent(const QCEvent& event);

    bool responseQuery(const QCQuery& query);

protected:
    virtual void changeEvent(QEvent* event) override;
    virtual void eventFilter(QObject* watched, QEvent* event) override;

private:

};

}

#endif // QT_CEF_VIEW_H
