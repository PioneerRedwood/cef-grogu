#ifndef CUSTOMQCVIEW_H
#define CUSTOMQCVIEW_H

#include "qcview/view.h"
#include "qcview/window.h"

class CustomQCView : public QCWindow
{
    Q_OBJECT
public:
    CustomQCView();
    ~CustomQCView();

    void changeColor();

protected:
    void OnUrlRequest(const QString& url) override {

    }
    void OnQueryRequest(const QCQuery& query) override {

    }
    void OnInvokeNotify(int browserId,
                                int frameId,
                                const QString& method
                                const QVariantList& arguments) override {

    }
private:

};

#endif // CUSTOMQCVIEW_H
