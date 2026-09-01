#include "mainwindow.h"
#include <QWidget>
#include <QDataStream>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent){
        server = new QTcpServer(this);
        socket = new QTcpSocket(this);
        //-->localhost = 127.0.0.1<--
        //Server می‌گوید من اینجا منتظرم
        //برنامه ی ما سروره 
        server->listen(QHostAddress::LocalHost,5000);
        //Socket، به پورت 5000 روی همین کامپیوتر وصل شو.
        //Client می‌گوید من می‌خواهم به همین‌جا وصل شوم
        //برنامه ی ما client
        socket->connectToHost(QHostAddress::LocalHost, 5000);


        connect(socket, &QTcpSocket::connected, this, [=]() {
            qDebug() << "Connected!";
            // socket->write("hello\n");
            QDataStream stream(socket);
            int number = 42;
            stream << number;
            QString word = "hello\n";
            stream << word;
        });
        connect(server, &QTcpServer::newConnection,this,[=](){
            QTcpSocket *clientSocket = server->nextPendingConnection();
            qDebug() << "A Client Connected!";
            
            connect(clientSocket, &QTcpSocket::readyRead, this, [=]() {
            // QByteArray data = clientSocket->readAll();
            // qDebug() << data;
            QDataStream stream(clientSocket);
            int number;
            QString word;
            stream >> number;
            qDebug() << number;
            stream >> word;
            qDebug() << word;
            });

        });
        
        
}
MainWindow::~MainWindow() = default;