#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QUdpSocket>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>

class Widget : public QWidget
{
    Q_OBJECT;

public:
    Widget(int port, QWidget *parent = 0);

private:
    QUdpSocket *mySocket;

    QListWidget *myListWidget;
    QLineEdit *myHttpAddress;
    QLineEdit *myPort;
    QLineEdit *myMessage;
    QPushButton *mySendButton;


    void createWidgets();
private slots:
    void readPendingDatagrams();
    void sendDatagram();
};

#endif // WIDGET_H
