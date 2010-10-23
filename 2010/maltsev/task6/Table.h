#ifndef TABLE_H
#define TABLE_H

#include <QDialog>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QUdpSocket>
#include <QByteArray>

const int BALL_RADIUS = 20;
const int BALL_AVERAGE_SPEED = 16;
const int BALL_TIMER_INTERVAL = 25;
const int TABLE_HEIGHT = 600;
const int TABLE_WIDTH = 800;
const int RACKET_HEIGHT = 20;
const int RACKET_HALFWIDTH = 80;
const int RACKET_SPEED = 20;

class Table: public QDialog {
Q_OBJECT;

public:
    Table(qint16, QWidget *w = 0);

private:
    struct Racket {
        int my_x, my_dx, my_height, my_width;
        void move();
    } my_racket;

    struct Ball {
        int my_x, my_y, my_r, my_rxEff, my_ryEff, my_dx, my_dy;
        void move(Racket&);
    } my_ball;

    int my_timerID;
    QUdpSocket *my_udpSocket;
    QHostAddress my_ip;
    qint16 my_port;

    void processTheDatagram(QByteArray datagram);

protected:
    virtual void paintEvent(QPaintEvent*);
    virtual void timerEvent(QTimerEvent*);

private slots:
    void readPendingDatagrams();

};

#endif
