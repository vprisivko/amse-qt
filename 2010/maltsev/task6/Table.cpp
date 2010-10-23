#include "Table.h"
#include <QPainter>
#include <QColor>
#include <QRect>
#include <QTime>

Table::Table(qint16 port, QWidget *parent): QDialog(parent) {
    setFixedSize(TABLE_WIDTH, TABLE_HEIGHT);

    my_racket.my_x = my_ball.my_x = TABLE_WIDTH / 2;
    my_racket.my_dx = 0;
    my_ball.my_y = TABLE_HEIGHT / 2;
    my_ball.my_r = BALL_RADIUS;
    QTime midnight(0, 0, 0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    my_ball.my_dx = qrand() % (BALL_AVERAGE_SPEED*2) - BALL_AVERAGE_SPEED;
    my_ball.my_dy = qrand() % (BALL_AVERAGE_SPEED*2) - BALL_AVERAGE_SPEED;
    my_timerID = startTimer(BALL_TIMER_INTERVAL);
    setWindowTitle(QString::number(port));
    my_ip.setAddress("127.0.0.1");
    my_port = port;
    my_udpSocket = new QUdpSocket(this);
    my_udpSocket->bind(my_ip, my_port);
    connect(my_udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
}

void Table::paintEvent(QPaintEvent* pe) {
    QPainter p(this);
    p.setPen(QPen(Qt::NoPen));
    p.setBrush(QBrush(QColor(0,150,0)));
    p.drawRect(pe->rect());
    p.setPen(QPen(Qt::SolidLine));
    p.setBrush(QBrush(QColor(200,0,0)));
    p.drawRect(my_racket.my_x - RACKET_HALFWIDTH, TABLE_HEIGHT - RACKET_HEIGHT, RACKET_HALFWIDTH *2, RACKET_HEIGHT);
    p.setBrush(QBrush(QColor(255,255,255)));
    p.drawEllipse(my_ball.my_x - my_ball.my_rxEff, my_ball.my_y - my_ball.my_ryEff, my_ball.my_rxEff * 2, my_ball.my_ryEff * 2);
}

void Table::timerEvent(QTimerEvent* e) {
    if (e->timerId() == my_timerID) {
        my_ball.move(my_racket);
        my_racket.move();
        my_racket.my_dx = 0;
        update();
    }
}

void Table::Racket::move() {
    my_x += my_dx;
    if (my_x + RACKET_HALFWIDTH > TABLE_WIDTH) {
        my_x -= my_dx;
    }
    if (my_x - RACKET_HALFWIDTH < 0) {
        my_x -= my_dx;
    }
}

void Table::Ball::move(Racket& racket) {
    my_x += my_dx;
    my_y += my_dy;
    my_rxEff = my_ryEff = my_r;
    if (my_x + my_r > TABLE_WIDTH) {
        my_rxEff = TABLE_WIDTH - my_x;
        if (my_x + my_r/2 > TABLE_WIDTH && my_dx > 0) {
            my_dx = -my_dx;
        }
    }
    if (my_x - my_r < 0) {
        my_rxEff = my_x;
        if (my_x - my_r/2 < 0 && my_dx < 0) {
           my_dx = -my_dx;
        }
    }
    if (my_y + my_r > TABLE_HEIGHT - RACKET_HEIGHT && my_x > racket.my_x - RACKET_HALFWIDTH && my_x < racket.my_x + RACKET_HALFWIDTH) {
        my_ryEff = TABLE_HEIGHT - RACKET_HEIGHT - my_y;
        if (my_y + my_r/2 > TABLE_HEIGHT - RACKET_HEIGHT && my_dy > 0) {
            my_dy = -my_dy;
        }
    }
    if (my_y + my_r > TABLE_HEIGHT) {
        my_x = TABLE_WIDTH / 2;
        my_y = TABLE_HEIGHT / 2;
        my_r = BALL_RADIUS;
        QTime midnight(0, 0, 0);
        qsrand(midnight.secsTo(QTime::currentTime()));
        my_dx = qrand() % (BALL_AVERAGE_SPEED*2) - BALL_AVERAGE_SPEED;
        my_dy = qrand() % (BALL_AVERAGE_SPEED*2) - BALL_AVERAGE_SPEED;
    }
    if (my_y - my_r < 0) {
        my_ryEff = my_y;
        if (my_y - my_r/2 < 0 && my_dy < 0) {
            my_dy = -my_dy;
        }
    }
}

void Table::readPendingDatagrams() {
    while (my_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(my_udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        my_udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);
        processTheDatagram(datagram);

    }
}

void Table::processTheDatagram(QByteArray datagram) {
    QString data(datagram);
    if (data == "Right") {
        my_racket.my_dx = RACKET_SPEED;
        return;
    }
    if (data == "Left") {
        my_racket.my_dx = -RACKET_SPEED;
        return;
    }
}
