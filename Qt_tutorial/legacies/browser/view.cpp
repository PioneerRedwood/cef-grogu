#include <QVBoxLayout>
#include <QWindow>
#include <QResizeEvent>
#include <QVariant>

#include <include/cef_app.h>
#include <include/cef_browser.h>
#include <include/cef_frame.h>
#include <include/cef_parser.h>
#include <include/cef_sandbox_win.h>

#include <qcview/common/protocol.h>
#include "qcview/common/event.h"
#include "qcview/common/cef_manager.h"
#include "qcview/common/cef_setting.h"


#include "qcview/browser/query.h"
#include "qcview/browser/view.h"
#include "qcview/browser/cef_window.h"
#include "qcview/browser/browser_handler.h"

namespace qcview {

class QCViewImpl
{
public:
  explicit Implementation(const QString& url, QCefView* view)
    : window_(nullptr)
    , handler_(nullptr)  {
    // Here we must create a QWidget as a wrapper to encapsulate the QWindow
    window_ = new CefWindow(view);
    window_->create();

    // Set window info
    CefWindowInfo window_info;
    RECT rc = { 0 };
    window_info.SetAsChild((HWND)window_->winId(), rc);

    for (auto cookieItem : CefSetting::global_cookie_list) {
      CefManager::getInstance().addCookie(cookieItem.name, cookieItem.value, cookieItem.domain, cookieItem.url);
    }

    CefBrowserSettings browserSettings;
    browserSettings.plugins = STATE_DISABLED; // disable all plugins

    // Create the browser
    handler_ = new QCefViewBrowserHandler(window_);

    // add archive mapping
    for (auto archiveMapping : archiveMappingList_) {
      handler_->AddArchiveResourceProvider(
        archiveMapping.path.toStdString(), archiveMapping.url.toStdString(), archiveMapping.psw.toStdString());
    }

    // add local folder mapping
    for (auto folderMapping : folderMappingList_) {
      handler_->AddLocalDirectoryResourceProvider(
        folderMapping.path.toStdString(), folderMapping.url.toStdString(), folderMapping.priority);
    }

    // Create the main browser window.
    if (!CefBrowserHost::CreateBrowser(window_info,       // window info
                                       handler_, // handler
                                       url.toStdString(), // url
                                       browserSettings,   // settings
                                       nullptr,
                                       CefRequestContext::GetGlobalContext())) {
      throw std::exception("Failed to create browser.");
    }
  }

  ~Implementation() {
    if (handler_) {
      handler_->CloseAllBrowsers(true);
      handler_ = nullptr;
    }
  }

  void closeAllBrowsers() {
    if (handler_) {
      handler_->CloseAllBrowsers(true);
    }
  }

  CefWindow* cefWindow() { return window_; }

  WId getCefWinId() {
    if (window_)
      return window_->winId();

    return 0;
  }

  void addLocalFolderResource(const QString& path, const QString& url) {
    if (handler_) {
      handler_->AddLocalDirectoryResourceProvider(path.toStdString(), url.toStdString());
    }
  }

  void addArchiveResource(const QString& path, const QString& url, const QString& password) {
    if (handler_) {
      handler_->AddArchiveResourceProvider(path.toStdString(), url.toStdString(), password.toStdString());
    }
  }

  void navigateToString(const QString& content) {
    if (handler_) {
      std::string data = content.toStdString();
      data = CefURIEncode(CefBase64Encode(data.c_str(), data.size()), false).ToString();
      data = "data:text/html;base64," + data;
      handler_->GetBrowser()->GetMainFrame()->LoadURL(data);
    }
  }

  void navigateToUrl(const QString& url) {
    if (handler_) {
      CefString strUrl;
      strUrl.FromString(url.toStdString());
      handler_->GetBrowser()->GetMainFrame()->LoadURL(strUrl);
    }
  }

  bool triggerEvent(
    const QString& name, 
    const QCefEvent& event, 
    int frameId = QCefViewBrowserHandler::MAIN_FRAME) {
    if (!name.isEmpty()) {
      return sendEventNotifyMessage(frameId, name, event);
    }

    return false;
  }

  bool responseQCefQuery(const QCefQuery& query) {
    if (handler_) {
      CefString res;
      res.FromString(query.response().toStdString());
      return handler_->ResponseQuery(query.id(), query.result(), res, query.error());
    }
    return false;
  }

  void notifyMoveOrResizeStarted() {
    if (handler_) {
      CefRefPtr<CefBrowser> browser = handler_->GetBrowser();
      if (browser) {
        CefRefPtr<CefBrowserHost> host = browser->GetHost();
        if (host)
          host->NotifyMoveOrResizeStarted();
      }
    }
  }

  bool sendEventNotifyMessage(
    int frameId, 
    const QString& name, 
    const QCefEvent& event) {
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
    for (QByteArray key : keys) {
      QVariant value = event.property(key.data());
      if (value.metaType() == QMetaType::Bool)
        dict->SetBool(key.data(), value.toBool());
      else if (value.type() == QMetaType::Int || value.type() == QMetaType::UInt)
        dict->SetInt(key.data(), value.toInt());
      else if (value.type() == QMetaType::Double)
        dict->SetDouble(key.data(), value.toDouble());
      else if (value.type() == QMetaType::QString) {
        cefStr.FromString(value.toString().toUtf8().constData());
        dict->SetString(key.data(), cefStr);
      } else {
      }
    }

    arguments->SetDictionary(idx++, dict);

    return handler_->TriggerEvent(frameId, msg);
  }

  void onToplevelWidgetMoveOrResize() { notifyMoveOrResizeStarted(); }

  void setContextMenuHandler(CefContextMenuHandler* handler) {
    if (handler_)
      handler_->SetContextMenuHandler(handler);
  }

  void setDialogHandler(CefDialogHandler* handler) {
    if (handler_)
      handler_->SetDialogHandler(handler);
  }

  void setDisplayHandler(CefDisplayHandler* handler) {
    if (handler_)
      handler_->SetDisplayHandler(handler);
  }

  void setDownloadHandler(CefDownloadHandler* handler) {
    if (handler_)
      handler_->SetDownloadHandler(handler);
  }

  void setJSDialogHandler(CefJSDialogHandler* handler) {
    if (handler_)
      handler_->SetJSDialogHandler(handler);
  }

  void setKeyboardHandler(CefKeyboardHandler* handler) {
    if (handler_)
      handler_->SetKeyboardHandler(handler);
  }

public:
  typedef struct FolderMapping
  {
    QString path;
    QString url;
    int priority;
  } FolderMapping;
  static QList<FolderMapping> folderMappingList_;

  typedef struct ArchiveMapping
  {
    QString path;
    QString url;
    QString psw;
  } ArchiveMapping;
  static QList<ArchiveMapping> archiveMappingList_;

private:
  QPointer<CefWindow> window_;

  CefRefPtr<QCefViewBrowserHandler> handler_;
};

QList<QCViewImpl::FolderMapping> QCViewImpl::folderMappingList_;
QList<QCViewImpl::ArchiveMapping> QCViewImpl::archiveMappingList_;

QCefView::QCefView(const QString url, QWidget* parent /*= 0*/)
  : QWidget(parent)
  , pImpl_(nullptr) {
  pImpl_ = std::make_unique<Implementation>(url, this);

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  setLayout(layout);

  QWidget* windowContainer = createWindowContainer(pImpl_->cefWindow(), this);
  layout->addWidget(windowContainer);

  // If we're already part of a window, we'll install our event handler
  // If our parent changes later, this will be handled in QCefView::changeEvent()
  if (this->window())
    this->window()->installEventFilter(this);
}

QCefView::QCefView(QWidget* parent /*= 0*/)
  : QCefView("about:blank", parent)
{}

QCefView::~QCefView() {
  disconnect();

  if (pImpl_)
    pImpl_.reset();
}

void QCefView::addLocalFolderResource(
  const QString& path, 
  const QString& url, 
  int priority /* = 0*/) {
  Implementation::folderMappingList_.push_back({ path, url, priority });
}

void QCefView::addArchiveResource(
  const QString& path, 
  const QString& url, 
  const QString& password /* = ""*/) {
  Implementation::archiveMappingList_.push_back({ path, url, password });
}

void QCefView::addCookie(
  const QString& name, 
  const QString& value, 
  const QString& domain, 
  const QString& url) {
  CefManager::getInstance().addCookie(
    name.toStdString(), value.toStdString(), domain.toStdString(), url.toStdString());
}

WId QCefView::getCefWinId() {
  if (pImpl_)
    return pImpl_->getCefWinId();

  return 0;
}

void QCefView::navigateToString(const QString& content) {
  if (pImpl_)
    pImpl_->navigateToString(content);
}

void QCefView::navigateToUrl(const QString& url) {
  if (pImpl_)
    pImpl_->navigateToUrl(url);
}

bool QCefView::browserCanGoBack() {
  if (pImpl_)
    return pImpl_->browserCanGoBack();

  return false;
}

bool QCefView::browserCanGoForward() {
  if (pImpl_)
    return pImpl_->browserCanGoForward();

  return false;
}

void QCefView::browserGoBack() {
  if (pImpl_)
    pImpl_->browserGoBack();
}

void QCefView::browserGoForward() {
  if (pImpl_)
    pImpl_->browserGoForward();
}

bool QCefView::browserIsLoading() {
  if (pImpl_)
    return pImpl_->browserIsLoading();

  return false;
}

void QCefView::browserReload() {
  if (pImpl_)
    pImpl_->browserReload();
}

void QCefView::browserStopLoad() {
  if (pImpl_)
    pImpl_->browserStopLoad();
}

bool QCefView::triggerEvent(const QCefEvent& event) {
  if (pImpl_)
    return pImpl_->triggerEvent(event.objectName(), event, QCefViewBrowserHandler::MAIN_FRAME);

  return false;
}

bool QCefView::triggerEvent(const QCefEvent& event, int frameId) {
  if (pImpl_)
    return pImpl_->triggerEvent(event.objectName(), event, frameId);

  return false;
}

bool QCefView::broadcastEvent(const QCefEvent& event) {
  if (pImpl_)
    return pImpl_->triggerEvent(event.objectName(), event, QCefViewBrowserHandler::ALL_FRAMES);

  return false;
}

bool QCefView::responseQCefQuery(const QCefQuery& query) {
  if (pImpl_)
    return pImpl_->responseQCefQuery(query);

  return false;
}

void QCefView::setContextMenuHandler(CefContextMenuHandler* handler) {
  if (pImpl_)
    return pImpl_->setContextMenuHandler(handler);
}

void QCefView::setDialogHandler(CefDialogHandler* handler) {
  if (pImpl_)
    return pImpl_->setDialogHandler(handler);
}

void QCefView::setDisplayHandler(CefDisplayHandler* handler) {
  if (pImpl_)
    return pImpl_->setDisplayHandler(handler);
}

void QCefView::setDownloadHandler(CefDownloadHandler* handler) {
  if (pImpl_)
    return pImpl_->setDownloadHandler(handler);
}

void QCefView::setJSDialogHandler(CefJSDialogHandler* handler) {
  if (pImpl_)
    return pImpl_->setJSDialogHandler(handler);
}

void QCefView::setKeyboardHandler(CefKeyboardHandler* handler) {
  if (pImpl_)
    return pImpl_->setKeyboardHandler(handler);
}

void QCefView::changeEvent(QEvent* event) {
  if (QEvent::ParentAboutToChange == event->type()) {
    if (this->window())
      this->window()->removeEventFilter(this);
  } else if (QEvent::ParentChange == event->type()) {
    if (this->window())
      this->window()->installEventFilter(this);
  }
  QWidget::changeEvent(event);
}

bool QCefView::eventFilter(QObject* watched, QEvent* event) {
  if (pImpl_ && watched == this->window()) {
    if (QEvent::Resize == event->type() || QEvent::Move == event->type())
      pImpl_->onToplevelWidgetMoveOrResize();
  }
  return QWidget::eventFilter(watched, event);
}
}