#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

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

    //
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
