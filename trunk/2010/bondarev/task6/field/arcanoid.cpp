#include <QPainter>
#include <QTime>
#include "arcanoid.h"

Arcanoid::Arcanoid(QHostAddress ip, qint16 port, QWidget *parent): QDialog(parent) {
    setBeginState();
    setNetworkData(ip, port);
    QTime t(0, 0, 0);
    qsrand(t.secsTo(QTime::currentTime()));
}

void Arcanoid::setBeginState() {
    countBallForGame = 3;
    gameOver = true;
    this->setFixedSize(640, 480);
    ball = new Ball();
    racket = new Racket();
}

void Arcanoid::setNetworkData(QHostAddress &host, qint16 port) {
    udpSocket = new QUdpSocket(this);
    myHost = host;
    myPort = port;
    udpSocket->bind(myHost, myPort);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readDatagrams()));
}

Arcanoid::Ball::Ball() {
    x = 320;
    y = 240;
    radius = 15;
    dx = 0;
    dy = 2;
}

Arcanoid::Racket::Racket() {
    width = 80;
    height = 30;
    x = 320;
    dx = 0;
}

void Arcanoid::readDatagrams() {
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray str;
        str.resize(udpSocket->pendingDatagramSize());
        QHostAddress fromIP;
        quint16 fromPort;
        udpSocket->readDatagram(str.data(), str.size(), &fromIP, &fromPort);
        toHost = fromIP;
        toPort = fromPort;
        parseDatagram(str);
    }
}

void Arcanoid::parseDatagram(QByteArray &str) {
    FieldXmlHandler *handler = new FieldXmlHandler(this);
    QXmlSimpleReader reader;
    reader.setContentHandler(handler);
    QXmlInputSource buf;
    buf.setData(str);
    reader.parse(&buf);
    delete handler;
}

void Arcanoid::timerEvent(QTimerEvent *) {
    racket->move(this);
    ball->move(racket, this);

    update();
}

void Arcanoid::Racket::move(Arcanoid *state) {
    x += dx;
    if (x - width/2 < 0) {
        dx = 0;
        x = width / 2;
        state->sendState();
    } else if (x + width/2 > 640) {
        dx = 0;
        x = 640 - width/2;
        state->sendState();
    } else if (x - width/2 < 3 || x + width/2 > 637){
        state->sendState();
    }
}

void Arcanoid::Ball::move(Arcanoid::Racket* racket, Arcanoid* state) {
    x += dx;
    y += dy;
    if (y + radius*2 >= 480 - racket->height && !(x <= racket->x - racket->width/2 || x >= racket->x + racket->width/2)) {
        dy = -dy;
    } else if (y + radius*2 >= 480 - racket->height) {
        if (state->countBallForGame > 0) {
            state->countBallForGame--;
            x = 320;
            y = 240;
            dx = qrand() % 10 + 1;
        } else {
            state->gameOver = true;
            state->ball->dx = 0;
            state->ball->dy = 0;
            state->racket->x = 320;
            state->racket->dx = 0;
            state->killTimer(state->timerId);
        }
        state->sendState();
    } else if (y <= 0) {
        dy = -dy;
    }
    if (x <= 0 || x + radius*2 >= 640) {
        dx = -dx;
    }
}

void Arcanoid::paintEvent(QPaintEvent *) {
    QGradient *gradient = new QRadialGradient(50,50,600);
    gradient->setColorAt(1, QColor::fromRgbF(0, 1, 0, 1));
    gradient->setColorAt(0, QColor::fromRgbF(1, 1, 1, 1));
    QPainter *painter = new QPainter(this);
    painter->begin(this);

    painter->setBrush(*gradient);
    painter->setPen(Qt::NoPen);
    painter->drawRect(0, 0, 640, 480);

    delete gradient;
    gradient = new QLinearGradient(racket->x, 480 - racket->height, racket->x, 480);
    gradient->setColorAt(0, QColor::fromRgbF(1, 0, 0, 1));
    gradient->setColorAt(1, QColor::fromRgb(0, 255, 0, 1));
    painter->setBrush(*gradient);
    painter->drawRect(racket->x - racket->width/2, 480 - racket->height, racket->width, 480);

    delete gradient;
    gradient = new QRadialGradient(ball->x + ball->radius/2, ball->y + ball->radius/2, ball->radius);
    gradient->setColorAt(1, QColor::fromRgbF(0, 0, 1, 1));
    gradient->setColorAt(0, QColor::fromRgbF(1, 1, 1, 1));
    painter->setBrush(*gradient);
    painter->drawEllipse(ball->x, ball->y, ball->radius*2, ball->radius*2);

    painter->setPen(QPen(Qt::SolidLine));
    painter->drawText(10, 10, "Balls for game: " + QString::number(countBallForGame));
    painter->drawText(10, 25, "ball x: " + QString::number(ball->x));
    painter->drawText(10, 40, "ball y: " + QString::number(ball->y));
}

bool Arcanoid::FieldXmlHandler::startElement(const QString&, const QString&, const QString &name, const QXmlAttributes &attrs) {
    if (name == "command") {
        if (attrs.value("value") == "start") {
            myField->countBallForGame = 3;
            myField->gameOver = false;
            myField->ball->x = 320;
            myField->timerId = myField->startTimer(25);
            myField->ball->y = 240;
            myField->ball->dx = qrand() % 6 + 1;
        } else if (attrs.value("value") == "left") {
            myField->racket->dx -= 1;
        } else if (attrs.value("value") == "right") {
            myField->racket->dx += 1;
        }
    }
    myField->sendState();
    return true;
}

void Arcanoid::sendState() {
    QDomDocument state = serialize();
    udpSocket->writeDatagram(state.toString().toAscii(), toHost, toPort);
}

QDomDocument Arcanoid::serialize() {
    QDomDocument doc;
    QDomElement state = doc.createElement("field");
    state.setAttribute("gameover", gameOver);
    state.setAttribute("width", 640);
    state.appendChild(ball->serialize(doc));
    state.appendChild(racket->serialize(doc));
    doc.appendChild(state);
    return doc;
}

QDomElement Arcanoid::Ball::serialize(QDomDocument &doc) {
    QDomElement ball = doc.createElement("ball");
    ball.setAttribute("x", x);
    ball.setAttribute("y", y);
    return ball;
}

QDomElement Arcanoid::Racket::serialize(QDomDocument &doc) {
    QDomElement racket = doc.createElement("racket");
    racket.setAttribute("halfracket", width/2);
    racket.setAttribute("x", x);
    return racket;
}
