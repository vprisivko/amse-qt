#ifndef MYCHAT_H
#define MYCHAT_H

#include <QUdpSocket>
#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>



class MyChat : public QDialog {
    Q_OBJECT;

public:
    MyChat(int);

private slots:
    void sendPressed();
    void newMessageArrived();

private:
    void showExplanation();
    void createDialog();
    void configureNetwork();

private:
    int portNumber;
    QListWidget* msgList;
    QPushButton* sendButton;
    QLineEdit* msgEdit;
    QLineEdit* ipEdit;
    QLineEdit* portEdit;
    QUdpSocket* myUdpSocket;
};

#endif // MYCHAT_H
