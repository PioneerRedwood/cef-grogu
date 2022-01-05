#ifndef QUERY_H
#define QUERY_H
#pragma once

#include <cstdint>

#include "QtCore/qglobal.h"
#include "QString"
#include "QPointer"
#include "QMetaType"

class QCQuery {
public:
    QCQuery();
    QCQuery(QString req, int64_t query);
    QCQuery(const QCQuery& other);

    QCQuery& operator=(const QCQuery& other);
    ~QCQuery();

    const QString request() const;
    const int64_t id() const;
    const QString response() const;

    const bool result() const;
    const int error() const;

    void setResponseResult(bool success, const QString& response, int error = 0) const;

private:
    int64_t id_;
    QString request_;
    mutable QString response_;

    mutable bool result_;
    mutable int error_;
};

//Q_DECLARE_METATYPE(QCQuery);


#endif // QUERY_H
