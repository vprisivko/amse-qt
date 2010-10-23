#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QIntValidator>
#include <QUdpSocket>
#include <QMessageBox>

class ChatDialog : public QDialog
{
    Q_OBJECT

private:
    QListWidget *myListWidget;
    QLineEdit *myLineEdIp;
    QLineEdit *myLineEdPort;
    QLineEdit *myLineEdMessage;
    QPushButton *myBtnSend;
    QUdpSocket * myUdpSocket;
public:
    ChatDialog(quint16 port, QWidget *parent = 0);
    ~ChatDialog();

public slots:
    void sendMessage();
    void reciveMessage();
};

#endif // CHATDIALOG_H
