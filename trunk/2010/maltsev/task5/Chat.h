#ifndef CHAT_H
#define CHAT_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QHostAddress>
#include <QUdpSocket>
#include <QByteArray>
#include <QListView>
#include <QStringListModel>

class Chat: public QDialog {
Q_OBJECT;

public:
    Chat(qint16 port = 2152, QWidget *parent = 0);

private:
    QStringListModel *my_model;
    QListView *my_list;
    QLineEdit *my_ipEdit, *my_portEdit, *my_inputEdit;
    QPushButton *my_sendButton, *my_setButton;
    QHostAddress my_ip, my_ipTo;
    qint16 my_port, my_portTo;
    QUdpSocket *my_udpSocket;
    bool isSet;

    void setView();
    void setNetworkData();
    void connectButtons();
    void processTheDatagram(QByteArray datagram);

private slots:
    void readPendingDatagrams();
    void setContact();
    void sendData();

};

#endif
