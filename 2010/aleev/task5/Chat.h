#ifndef _CHAT_H_
#define _CHAT_H_

#include <QWidget>
#include <QDialog>
#include <QListWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QUdpSocket>

class Chat : public QDialog {
    Q_OBJECT;

public:
    Chat(quint16 port, QWidget *parent = 0);

private:
    void createWidgets();
    void connectAll();

public slots:
    void recvFrom();
    void sendTo();

private:
    QUdpSocket *myUdpSocket;
    qint16 myPort;
    QListWidget *myHistory;
    QLineEdit *myListenerIp;
    QLineEdit *myListenerPort;
    QTextEdit *myMessageTE;
    QPushButton *mySendButton;
};

#endif
