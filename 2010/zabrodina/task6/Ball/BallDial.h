#ifndef BALLDIAL_H
#define BALLDIAL_H

#include <QtGui/QDialog>
#include<QPushButton>
#include<QDialog>
#include<QPainter>
#include<QPaintEvent>
#include<QTimerEvent>
#include<QTimer>
#include<QtNetwork/QUdpSocket>
#include<QtNetwork/QHostAddress>
#include<QByteArray>
#include"State.h"
class BallDial : public QDialog
{
    Q_OBJECT;

public:
    State *state;
    QPainter *p;
    QTimer *bTimer;
    QUdpSocket *socket;
    QHostAddress ip;
    qint16 port;
    BallDial(QHostAddress _ip, qint16 _port);
    void paintEvent( QPaintEvent *);
public slots:
    void timeEvent();
    void readMessage();
    void sendMessage();
};

#endif // BALLDIAL_H
