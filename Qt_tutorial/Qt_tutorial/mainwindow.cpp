#include <iostream>

#include "QHBoxLayout"
#include "QDir"
#include "QCoreApplication"

#include "mainwindow.h"
#include "./ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWindow()
{
    // MainWindow settings
    this->setWindowFlags(Qt::CustomizeWindowHint);
    this->setWindowFlags(Qt::FramelessWindowHint);

    // cotrolFrame's elements settings
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(closeWindow()));
    connect(ui->minimizeButton, SIGNAL(clicked()), this, SLOT(minimizeWindow()));

    // add custom widget

//    QHBoxLayout *layout = new QHBoxLayout();
//    layout->setContentsMargins(1, 1, 1, 1);
//    layout->setSpacing(3);
//    layout->addWidget(ui->cefBrowseWidget);
//    QDir dir = QCoreApplication::applicationDirPath();
//    QString uri = QDir::toNativeSeparators(dir.filePath("..html"));
//    qcview_ = new qcview::QCView(uri, this);
//    ui->cefBrowseWidget->layout()->addWidget(qcview_);
//    layout->addWidget(ui->cefBrowseWidget);



}

void MainWindow::closeWindow()
{
    // CloseButton clicked
    auto button = QObject::sender();
    if(button == ui->closeButton)
    {
        qDebug() << "shutdown()\n";
        this->close();
    }
}

void MainWindow::minimizeWindow()
{
    this->showMinimized();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // check z-order
    qDebug() << event;
    oldPos = event->globalPosition();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    const QPointF delta = event->globalPosition() - oldPos;
    move(x()+delta.x(), y() + delta.y());
    oldPos = event->globalPosition();
}
