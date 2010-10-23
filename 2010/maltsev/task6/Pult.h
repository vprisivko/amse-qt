#ifndef PULT_H
#define PULT_H

#include <QDialog>
#include <QUdpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QPushButton>
#include <QLineEdit>

const int BUTTON_INTERVAL = 25;

class Pult: public QDialog {
Q_OBJECT;

public:
    Pult(qint16, QWidget *w = 0);

private:
    QPushButton *my_leftButton, *my_rightButton, *my_setButton, *my_startButton;
    QLineEdit *my_ipEdit, *my_portEdit;
    QUdpSocket *my_udpSocket;
    QHostAddress my_ip, my_ipTo;
    qint16 my_port, my_portTo;
    bool isSet;

    void setView();
    void setNetworkData();
    void connectButtons();

private slots:
    void sendRight();
    void sendLeft();
    void setContact();
    void sendStart();

};

#endif
