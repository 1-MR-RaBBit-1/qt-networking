#include "mainwindow.h"
#include <QDataStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QLineEdit *message = new QLineEdit(this);
    message->setPlaceholderText("no message yet ...");
    message->setReadOnly(true);



    server = new QTcpServer(this);

    server->listen(QHostAddress::LocalHost, 5000);

    qDebug() << "Server is listening...";
    
    connect(server, &QTcpServer::newConnection, this, [=]() {

        QTcpSocket *clientSocket = server->nextPendingConnection();

        connect(clientSocket, &QTcpSocket::readyRead, this, [=](){
            QDataStream stream(clientSocket);
            QString text;
            stream >> text;
            message->setText(text);
            // QMessageBox::information(this,"Received Data",text);
            // qDebug() << text;
        });

        qDebug() << "Client connected!";

    });
}

MainWindow::~MainWindow() = default;