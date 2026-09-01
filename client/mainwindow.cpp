#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    socket = new QTcpSocket(this);

    socket->connectToHost(QHostAddress::LocalHost, 5000);

    connect(socket, &QTcpSocket::connected, this, [=]() {
        qDebug() << "Connected to server!";
    });
}

MainWindow::~MainWindow() = default;