#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
/*
QTcpServer → برای ساختن برنامه‌ای که منتظر اتصال TCP می‌ماند.
QTcpSocket → برای برقراری ارتباط TCP با یک مقصد.
*/

class MainWindow:public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QTcpServer *server;
    QTcpSocket *socket;
};

#endif //MAINWINDOW_H