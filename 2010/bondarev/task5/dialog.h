#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <QDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QByteArray>
#include <QHostAddress>
#include <QUdpSocket>
#include <QTextEdit>
#include <QStringListModel>


class Dialog : public QDialog {
    Q_OBJECT

private:
    QListWidget *messageBox;
    QLineEdit *lineIP;
    QLineEdit *linePort;
    QLineEdit *lineMessage;
    QPushButton *bnSend;

    int fromPort;

    QUdpSocket *socket;

    void createMainWindow();
    void connects();
    void setConnectionData();

public:
    Dialog(int port = 10000, QWidget *parent = 0);

    ~Dialog();

public slots:
    void ssendMessage();
    void readDatagrams();
};

#endif
