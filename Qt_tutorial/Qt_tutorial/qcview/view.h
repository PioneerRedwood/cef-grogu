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

#include "cef_binary_win64/include/cef_client.h"
#include "cef_binary_win64/include/cef_app.h"
#include "cef_binary_win64/include/cef_browser.h"
#include "cef_binary_win64/include/cef_frame.h"
#include "cef_binary_win64/include/cef_parser.h"

#include "qcview/handler.h"
#include "qcview/protocol.h"
#include "qcview/window.h"
#include "qcview/event.h"
#include "qcview/query.h"
#include "qcview/view_delegate.h"

class CefContextMenuHandler;
class CefDisplayHandler;
class CefLifeSpanHandler;
class CefLoadHandler;
class QCWindow;

class QCView : public QWidget
{
    Q_OBJECT
public:
    QCView(const QString &url, QWidget *parent = 0)
        :
          handler_(nullptr),
          parent_(parent)

    {
        // create a QWidget
        CefWindowHandle hwnd = (CefWindowHandle)parent_->winId();

        CefWindowInfo window_info;
        CefRect rc(0, 0, 100, 100);
        window_info.SetAsChild(hwnd, rc);

        // all cookie item add to CefManager

        CefBrowserSettings browserSettings;
        browserSettings.plugins = STATE_DISABLED;

        handler_ = new QCHandler(this);
//        handler_ = new QCHandler(reinterpret_cast<QCView*>(this));


        // add archive mapping

        // add local folder mapping

        if (!CefBrowserHost::CreateBrowser(window_info,
                                           handler_,
                                           url.toStdString(),
                                           browserSettings,
                                           nullptr,
                                           CefRequestContext::GetGlobalContext()))
        {
            throw std::exception("Failed to create browser.");
        }
    }
    QCView(QWidget *parent = 0)
        : QCView("about:blank", parent) {}
    ~QCView()
    {
        //        QWidget::disconnect();
        handler_->CloseAllBrowsers(true);
    }

    //    util
    static void addLocalFolderResource(const QString &path,
                                       const QString &url,
                                       int priority = 0)
    {
    }

    static void addArchiveResource(const QString &path,
                                   const QString &url,
                                   const QString &password = 0)
    {
    }

    void addCookie(const QString &name,
                   const QString &value,
                   const QString &domain,
                   const QString &url)
    {
        //CefManager addCookie
    }
    //  browser
    WId getWinId()
    {
        if (parent_)
            parent_->winId();
        return 0;
    }

    void navigateToString(const QString &content)
    {
        if (handler_)
        {
            std::string data = content.toStdString();
            data = CefURIEncode(CefBase64Encode(data.c_str(), data.size()), false).ToString();
            data = "data:text/html;base64," + data;
            handler_->GetBrowser()->GetMainFrame()->LoadURL(data);
        }
    }
    void navigateToUrl(const QString &url)
    {
        if (handler_)
        {
            CefString strUrl;
            strUrl.FromString(url.toStdString());
            handler_->GetBrowser()->GetMainFrame()->LoadURL(strUrl);
        }
    }
    bool browserCanGoBack()
    {
        return handler_->GetBrowser()->CanGoBack();
    }
    bool browserCanGoForward()
    {
        return handler_->GetBrowser()->CanGoForward();
    }
    void browserGoBack()
    {
        return handler_->GetBrowser()->GoBack();
    }
    void browserGoForward()
    {
        return handler_->GetBrowser()->GoForward();
    }
    bool browserIsLoading()
    {
        return handler_->GetBrowser()->IsLoading();
    }
    bool browserReload()
    {
        handler_->GetBrowser()->Reload();
    }
    bool browserStopLoad()
    {
        handler_->GetBrowser()->StopLoad();
    }
    bool triggerEvent(const QCEvent &event, int frameId = int(QCHandler::FRAME_TYPE::MAIN_FRAME))
    {
        // trigger event for specific frame
        sendEventNotifyMessage(frameId, event.objectName(), event);
    }
    bool broadcastEvent(const QCEvent &event)
    {
        // broadcast event for all frames
        sendEventNotifyMessage(int(QCHandler::FRAME_TYPE::ALL_FRAMES), event.objectName(), event);
    }
    bool responseQuery(const QCQuery &query)
    {
        CefString res;
        res.FromString(query.response().toStdString());
        return handler_->ResponseQuery(query.id(), query.result(), res, query.error());
    }
    void notifyMoveOrResizeStarted()
    {
    }
    bool sendEventNotifyMessage(int frameId,
                                const QString &name,
                                const QCEvent &event)
    {

        CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(TRIGGEREVENT_NOTIFY_MESSAGE);
        CefRefPtr<CefListValue> arguments = msg->GetArgumentList();

        int idx = 0;
        CefString eventName = name.toStdString();
        arguments->SetString(idx++, eventName);

        CefRefPtr<CefDictionaryValue> dict = CefDictionaryValue::Create();

        CefString cefStr;
        cefStr.FromString(event.objectName().toUtf8().constData());
        dict->SetString("name", cefStr);

        QList<QByteArray> keys = event.dynamicPropertyNames();
        for (QByteArray key : keys)
        {
            //          QVariant value = event.property(key.data());
            //          if (value.metaType() == QMetaType::Bool)
            //            dict->SetBool(key.data(), value.toBool());
            //          else if (value.metaType() == QMetaType::Int || value.type() == QMetaType::UInt)
            //            dict->SetInt(key.data(), value.toInt());
            //          else if (value.metaType() == QMetaType::Double)
            //            dict->SetDouble(key.data(), value.toDouble());
            //          else if (value.metaType() == QMetaType::QString) {
            //            cefStr.FromString(value.toString().toUtf8().constData());
            //            dict->SetString(key.data(), cefStr);
            //          }
        }
    }

    void onMoveOrResize() { notifyMoveOrResizeStarted(); }

    //    handler
    //    void setContextMenuHandler(CefContextMenuHandler* handler) {
    //    }

    //    void setDisplayHandler(CefDisplayHandler* handler) {
    //    }

protected:
    virtual void changeEvent(QEvent *event) override
    {
        if (QEvent::ParentAboutToChange == event->type())
        {
            if (this->window())
            {
                this->window()->removeEventFilter(this);
            }
            else if (QEvent::ParentChange == event->type())
            {
                if (this->window())
                {
                    this->window()->installEventFilter(this);
                }
            }
        }
        QWidget::changeEvent(event);
    }
    virtual bool eventFilter(QObject *watched, QEvent *event) override
    {
        if (watched == this->window())
        {
            if (QEvent::Resize == event->type() || QEvent::Move == event->type())
            {
                onMoveOrResize();
            }
        }
        return QWidget::eventFilter(watched, event);
    }

private:
    QWidget* parent_;
    CefRefPtr<QCHandler> handler_;
};

#endif // QT_CEF_VIEW_H
