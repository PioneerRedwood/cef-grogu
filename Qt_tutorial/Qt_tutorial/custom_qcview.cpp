#include <windows.h>
#include "QMessageBox"
#include "QColor"
#include "QRandomGenerator"

#include "qcview/event
#include "custom_qcview.h"


CustomQCView::CustomQCView()
{

}

CustomQCView::~CustomQCView() {}

void CustomQCView::changeColor() {
    QColor color(QRandomGenerator::global()->generate());

    QCEvent event("colorChange");
//    event.setStringProperty()
}

void CustomQCView::OnUrlRequest(const QString& url) {

}

void CustomQCView::OnQueryRequest(const QCQuery& query) {

}

void CustomQCView::OnInvokeNotify(int browserId,
                                  int frameId,
                                  const QString &method) {

}
