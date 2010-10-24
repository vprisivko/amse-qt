#ifndef _CHAT_DIALOG_H_
#define _CHAT_DIALOG_H_

#include <QDialog>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>

class UDPChatDialog : public QDialog{
    Q_OBJECT;

    public:
        UDPChatDialog ( QWidget* parent = NULL, int newPort = 10000 );
    public slots:
        void readMessage();
        void writeMessage();
    private:
        void createWidgets();
        void createSocket();
        void addWidgets();
        void setConnection();
    private:   
        QListWidget* messageList;
        QLabel* ipLabel;
        QLineEdit* ipTextBox;
        QLabel* portLabel;
        QLineEdit* portTextBox;
        QLabel* messageLabel;
        QTextEdit* messageTextBox;
        QPushButton* sendButton;
        QUdpSocket* udpSocket;
    private:
        int port;
};

#endif
