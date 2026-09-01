#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    server = new QTcpServer(this);

    server->listen(QHostAddress::LocalHost, 5000);

    qDebug() << "Server is listening...";
    
    connect(server, &QTcpServer::newConnection, this, [=]() {

        QTcpSocket *clientSocket = server->nextPendingConnection();

        qDebug() << "Client connected!";

    });
}

MainWindow::~MainWindow() = default;