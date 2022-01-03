#include <QtCore/qglobal.h>
#include <QObject>
#include <QString>
#include <QVariant>

#include <include/cef_app.h>
#include <include/wrapper/cef_message_router.h>

#ifdef QCEFVIEW_LIB
#define QCEFVIEW_EXPORT Q_DECL_EXPORT
#else
  #define QCEFVIEW_EXPORT Q_DECL_IMPORT
  #if _WIN32
  #pragma comment(lib, "QCefView.lib")
  #endif
#endif

namespace qcview {
class QCEFVIEW_EXPORT QCefEvent : public QObject
{
  Q_OBJECT

public:
  QCefEvent()
    : QObject(nullptr)
  {}

  QCefEvent(const QString& name)
    : QObject() {
    setObjectName(name);
  }

  void setEventName(const QString& name) {
    setObjectName(name);
  }

  void setIntProperty(const QString& key, int value) {
    Q_ASSERT(0 != QString::compare(key, "name", Qt::CaseInsensitive));
    setProperty(key.toUtf8().constData(), QVariant::fromValue(value));
  }

  void setDoubleProperty(const QString& key, double value) {
    Q_ASSERT(0 != QString::compare(key, "name", Qt::CaseInsensitive));
    setProperty(key.toUtf8().constData(), QVariant::fromValue(value));
  }

  void setStringProperty(const QString& key, const QString& value) {
    Q_ASSERT(0 != QString::compare(key, "name", Qt::CaseInsensitive));
    setProperty(key.toUtf8().constData(), QVariant::fromValue(value));
  }

  void setBoolProperty(const QString& key, bool value) {
    Q_ASSERT(0 != QString::compare(key, "name", Qt::CaseInsensitive));
    setProperty(key.toUtf8().constData(), QVariant::fromValue(value));
  }
};

}