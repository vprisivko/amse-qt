#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QtGui/QDialog>
#include <QtNetwork/QUdpSocket>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <exception>


class ChatDialog : public QDialog
{
    Q_OBJECT;

public:
    ChatDialog( int portNumber = 12345, QWidget *parent = 0);
    ~ChatDialog();

private slots:
    void sendMessage();
    void recieveMessage();

signals:
    void newLineInChat();

private:
    QListWidget * chatList;
    QLineEdit * linePortNumber;
    QLineEdit * lineIP;
    QLineEdit * lineMessage;
    QPushButton * sendButton;

    QUdpSocket * chatSocket;

    static const int MAX_LEN = 10000;
    char * recievedData;

    void createChatDialog();
    void createSocket( int portNumber );
    void connectAll();

    void addChatMessage( QString msg, QString from );
};

#endif // CHATDIALOG_H
