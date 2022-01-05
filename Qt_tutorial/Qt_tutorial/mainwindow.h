#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

// #include "qcview/view.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void closeWindow();
    void minimizeWindow();

    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);

private:
    void initWindow();

    Ui::MainWindow *ui;
//    qcview::QCView *qcview_;

    QPointF oldPos;
};
#endif // MAINWINDOW_H
