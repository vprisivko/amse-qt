#ifndef UDPCHATDIALOG_H
#define UDPCHATDIALOG_H

#include <QtGui/QDialog>
#include<QtNetwork/QUdpSocket>
#include<QtNetwork/QHostAddress>
#include<QLineEdit>
#include<QTextEdit>
#include<QPushButton>
#include<QListWidget>
#include<QLabel>
class UdpChatDialog : public  QDialog {
    Q_OBJECT;
public:
    UdpChatDialog(int _port);
   void createWidgets();
   void addWidgets();
   void connectWidgets();

private:
    int port;
    QUdpSocket *udpSocket;
    QListWidget *chatArea;
    QLabel *ip;
    QLineEdit *ipArea;
    QLineEdit *listenPort;
    QLabel *p;
    QTextEdit *inputText;
    QPushButton *sendButton;
public slots:
    void readMessage();
    void sendMessage();
};

#endif // UDPCHATDIALOG_H
