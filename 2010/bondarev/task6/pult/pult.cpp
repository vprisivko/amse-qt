#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHostAddress>
#include <QDebug>
#include "pult.h"

Pult::Pult(char *myIp, int myPort, char* toIp, int toPort, QWidget *parent) : QDialog(parent) {
    setNetworkData(myIp, myPort);
    this->toHost = QHostAddress(QString(toIp));
    this->toPort = toPort;
    setWidgets();
    connects();
}

void Pult::setNetworkData(char *ip, int port) {
    udpSocket = new QUdpSocket(this);
    myHost = QString(ip);
    myPort = port;
    udpSocket->bind(myHost, myPort);

    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readDatagrams()));
}

void Pult::readDatagrams() {
    qDebug() << "read datagrams ";
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress fromIP;
        quint16 fromPort;
        udpSocket->readDatagram(datagram.data(), datagram.size(), &fromIP, &fromPort );
        toHost = fromIP;
        toPort = fromPort;
        parseDatagramm(datagram);
    }
    qDebug() << "from " << toHost << " and port " << toPort;
}

void Pult::setWidgets() {
    bnStart = new QPushButton("Start!", this);
    bnLeft = new QPushButton("<=", this);
    bnRight = new QPushButton("=>", this);
    bnStart->setEnabled(true);
    bnLeft->setEnabled(false);
    bnRight->setEnabled(false);

    QVBoxLayout *mainLay = new QVBoxLayout(this);
    QHBoxLayout *controls = new QHBoxLayout();

    controls->addWidget(bnLeft);
    controls->addWidget(bnRight);

    mainLay->addWidget(bnStart);
    mainLay->addItem(controls);
}

void Pult::connects() {
    connect(bnStart, SIGNAL(pressed()), this, SLOT(pushStart()));
    connect(bnLeft, SIGNAL(pressed()), this, SLOT(pushLeft()));
    connect(bnRight, SIGNAL(pressed()), this, SLOT(pushRight()));
}

void Pult::pushStart() {
    udpSocket->writeDatagram("<command value = \"start\" />", toHost, toPort);
}

void Pult::pushLeft() {
    udpSocket->writeDatagram("<command value = \"left\" />", toHost, toPort);
}

void Pult::pushRight() {
    udpSocket->writeDatagram("<command value = \"right\" />", toHost, toPort);
}

Pult::State* Pult::State::createInstance(const QByteArray &str) {
    Pult::State *state = new Pult::State();
    Pult::PultXmlHandler* handler = new Pult::PultXmlHandler(state);
    QXmlSimpleReader reader;
    reader.setContentHandler(handler);
    QXmlInputSource buf;
    buf.setData(str);
    reader.parse(&buf);
    delete handler;
    return state;
}

bool Pult::PultXmlHandler::startElement(const QString&, const QString&, const QString &name, const QXmlAttributes &attrs) {
    if (name == "field") {
        state->gameOver = attrs.value("gameover") == "1";
        state->fieldWidth = attrs.value("width").toInt();
    } else if (name == "ball") {
        state->ballX = attrs.value("x").toInt();
        state->ballY = attrs.value("y").toInt();
        state->ballRadius = attrs.value("radius").toInt();
    } else if (name == "racket") {
        state->racketHalfWidth = attrs.value("halfracket").toInt();
        state->racketX = attrs.value("x").toInt();
    }
    return true;
}

void Pult::parseDatagramm(QByteArray &str) {
    Pult::State *state = Pult::State::createInstance(str);
    if (state->gameOver) {
        qDebug() << "gameOver";
        bnStart->setEnabled(true);
        bnLeft->setEnabled(false);
        bnRight->setEnabled(false);
    } else {
        bnStart->setEnabled(false);
        if (state->racketX + state->racketHalfWidth >= state->fieldWidth) {
            bnRight->setEnabled(false);
        } else {
            bnRight->setEnabled(true);
        }
        if (state->racketX - state->racketHalfWidth <= 0) {
            bnLeft->setEnabled(false);
        } else {
            bnLeft->setEnabled(true);
        }
    }
    delete state;
}
