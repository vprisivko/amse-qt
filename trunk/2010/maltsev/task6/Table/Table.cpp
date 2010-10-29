#include "Table.h"
#include <QPainter>
#include <QColor>
#include <QRect>
#include <QTime>
#include <QXmlSimpleReader>
#include <QXmlInputSource>
#include <QMessageBox>

Table::Table(QHostAddress& ip, qint16 port, QWidget *parent): QDialog(parent) {
    setFixedSize(TABLE_WIDTH, TABLE_HEIGHT);
    started = false;
    my_racket.my_x = my_ball.my_x = TABLE_WIDTH / 2;
    my_racket.my_dx = 0;
    my_ball.my_y = TABLE_HEIGHT - BALL_RADIUS - RACKET_HEIGHT;
    my_ball.my_r = BALL_RADIUS;
    QTime midnight(0, 0, 0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    my_ball.my_dx = 0;
    my_ball.my_dy = 0;
    my_ballTimerID = startTimer(BALL_TIMER_INTERVAL);
    my_stateTimerID = startTimer(SEND_TIMER_INTERVAL);
    setWindowTitle(QString::number(port));
    my_ip = ip;
    my_port = port;
    my_udpSocket = new QUdpSocket(this);
    my_udpSocket->bind(my_ip, my_port);
    connect(my_udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
    pultConnected = false;
    gameOver = false;
    my_ballsNumber = BALLS_NUMBER;
}

Table::~Table() {
    if (pultConnected) {
        gameOver = true;
        sendState();
    }
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
    p.drawText(TABLE_WIDTH - 50, 10, "Balls: " + QString::number(my_ballsNumber));
}

void Table::timerEvent(QTimerEvent* e) {
    if (e->timerId() == my_ballTimerID) {
        my_racket.move();
        my_ball.move(my_racket, this);
        if (!started) {
            my_ball.my_x = my_racket.my_x;
        }
        update();
    }
    if (e->timerId() == my_stateTimerID && pultConnected) {
        sendState();
    }
}

void Table::Racket::move() {
    my_x += my_dx;
    if (my_x + RACKET_HALFWIDTH > TABLE_WIDTH) {
        my_x -= my_dx;
        my_dx = 0;
    }
    if (my_x - RACKET_HALFWIDTH < 0) {
        my_x -= my_dx;
        my_dx = 0;
    }
}

void Table::Ball::move(Racket& racket, Table* table) {
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
        racket.my_x = my_x = TABLE_WIDTH / 2;
        my_y = TABLE_HEIGHT - BALL_RADIUS - RACKET_HEIGHT;
        my_r = BALL_RADIUS;
        QTime midnight(0, 0, 0);
        qsrand(midnight.secsTo(QTime::currentTime()));
        my_dx = 0;
        my_dy = 0;
        table->started = false;
        table->loseBall();
    }
    if (my_y - my_r < 0) {
        my_ryEff = my_y;
        if (my_y - my_r/2 < 0 && my_dy < 0) {
            my_dy = -my_dy;
        }
    }
}

QDomElement Table::Ball::serialize(QDomDocument &doc) {
    QDomElement element = doc.createElement("ball");
    element.setAttribute("x", my_x);
    element.setAttribute("y", my_y);
    return element;
}

QDomElement Table::Racket::serialize(QDomDocument &doc) {
    QDomElement element = doc.createElement("racket");
    element.setAttribute("x", my_x);
    element.setAttribute("halfwidth", RACKET_HALFWIDTH);
    return element;
}

void Table::readPendingDatagrams() {
    while (my_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(my_udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        my_udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);
        if (!pultConnected) {
            my_ipTemp = sender;
            my_portTemp = senderPort;
        }
        if (my_ipTemp == sender && my_portTemp == senderPort) {
            processTheDatagram(datagram);
        }

    }
}

void Table::processTheDatagram(QByteArray datagram) {
    QXmlSimpleReader reader;
    reader.setContentHandler(new Table::TableXmlHandler(this));
    QXmlInputSource buf;
    buf.setData(datagram);
    reader.parse(&buf);

}

QDomDocument Table::serialize() {
    QDomDocument doc;
    QDomElement state = doc.createElement("state");
    state.setAttribute("started", started);
    state.setAttribute("gameover", gameOver);
    state.setAttribute("height", TABLE_HEIGHT);
    state.setAttribute("width", TABLE_WIDTH);
    state.appendChild(my_ball.serialize(doc));
    state.appendChild(my_racket.serialize(doc));
    doc.appendChild(state);
    return doc;
}

void Table::sendState() {
    QDomDocument state = serialize();
    //qDebug() << state.toString();
    my_udpSocket->writeDatagram(state.toString().toAscii(), my_ipTo, my_portTo);
}

bool Table::TableXmlHandler::startElement(const QString &, const QString &, const QString & qName, const QXmlAttributes & atts) {
    if (!my_table->pultConnected) {
        if (qName == "set") {
            my_table->pultConnected = true;
            my_table->my_ipTo =  my_table->my_ipTemp;
            my_table->my_portTo =  my_table->my_portTemp;
        }
        return true;
    }
    if (qName == "command") {
        if (atts.value("name") == "start" && !my_table->started) {
            my_table->started = true;
            my_table->my_ball.my_dx = qrand() % (BALL_AVERAGE_SPEED*2) - BALL_AVERAGE_SPEED;
            my_table->my_ball.my_dy = -(qrand() % (BALL_AVERAGE_SPEED - 1) + 1);
            return true;
        }
        if (atts.value("name") == "right") {
            my_table->my_racket.my_dx = RACKET_SPEED;
            return true;
        }
        if (atts.value("name") == "left") {
            my_table->my_racket.my_dx = -RACKET_SPEED;
            return true;
        }
        if (atts.value("name") == "stop") {
            my_table->my_racket.my_dx = 0;
            return true;
        }
    }
    return true;
}

void Table::loseBall() {
    if (my_ballsNumber == 0) {
        gameOver = true;
        sendState();
        QMessageBox gOver;
        gOver.setText("Game Over.");
        gOver.exec();
        close();
        return;
    }
    --my_ballsNumber;
}
