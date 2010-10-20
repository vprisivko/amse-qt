#ifndef SIMPLEUDPCHAT_H
#define SIMPLEUDPCHAT_H

#include <QtGui/QDialog>
#include <QtNetwork/QUdpSocket>
#include <QtGui/QListWidget>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

class SimpleUDPChat : public QDialog {
    Q_OBJECT

public:
    SimpleUDPChat(QWidget *parent = 0);

    bool startUdpListener(int port);

private:
    QListWidget * messagesList;
    QLineEdit * ipAddressText;
    QLineEdit * portText;
    QLineEdit * messageText;
    QPushButton * sendButton;
    QUdpSocket * udpSocket;

    void constructObjects();
    void connectObjects();

private slots:
    void sendMessage();
    void readMessage();
};

#endif // SIMPLEUDPCHAT_H
