#ifndef EVENT_H
#define EVENT_H

#include "QtCore/qglobal.h"
#include "QObject"
#include "QString"
#include "QVariant"

#include "include/cef_app.h"
#include "include/wrapper/cef_message_router.h"


class QCEvent : public QObject {
    Q_OBJECT
public:
    QCEvent()
    : QObject(nullptr) {}
    QCEvent(const QString& name)
        :QObject() {
        setObjectName(name);
    }

    void setEventName(const QString& name) {
        setObjectName(name);
    }

    template<typename T>
    void setProperty(const QString& key, T value) {
        Q_ASSERT(0 != QString::compare(key, "name", Qt::CaseInsensitive));
        setProperty(key.toUtf8().constData(), QVariant::fromValue(value));
    }

//    void setIntProperty(const QString& key, int value) {
//        Q_ASSERT(0 != QString::compare(key, "name", Qt::CaseInsensitive));
//        setProperty(key.toUtf8().constData(), QVariant::fromValue(value));
//    }

//    void setDoubleProperty(const QString& key, double value) {
//        Q_ASSERT(0 != QString::compare(key, "name", Qt::CaseInsensitive));
//        setProperty(key.toUtf8().constData(), QVariant::fromValue(value));
//    }

//    void setStringProperty(const QString& key, const QString& value) {
//        Q_ASSERT(0 != QString::compare(key, "name", Qt::CaseInsensitive));
//        setProperty(key.toUtf8().constData(), QVariant::fromValue(value));
//    }

//    void setBoolProperty(const QString& key, bool value) {
//        Q_ASSERT(0 != QString::compare(key, "name", Qt::CaseInsensitive));
//        setProperty(key.toUtf8().constData(), QVariant::fromValue(value));
//    }
};


#endif // EVENT_H
