#include <QPainter>
#include <QXmlSimpleReader>
#include <QMessageBox>
#include <algorithm> // for min algorithm
#include "BallDialog.h"

BallDialog::BallDialog(QHostAddress address, quint16 port, QHostAddress destinationAddress, quint16 destinationPort,
                       int dx, int dy, int rx, int ry, int time, QWidget *parent)
                           : QDialog(parent) {
    myRacket = new Racket(50, 10, 200);
    myBall = new Ball(rx, ry, dx, dy, 200);
    myDestinationAddress = destinationAddress;
    myDestinationPort = destinationPort;
    mySocket = new QUdpSocket(this);
    mySocket->bind(address, port);

    myIsStarted = false;
    myRacketSpeed = 50;
    myBallsLeft = myBallsCount = 3;

    startTimer(time);

    setMinimumWidth(200);
    setMinimumHeight(200);

    connect(mySocket, SIGNAL(readyRead()), this, SLOT(readDatagrams()));
}

BallDialog::~BallDialog() {
    delete myBall;
    delete myRacket;
}

void BallDialog::timerEvent(QTimerEvent *) {
    if (myIsStarted) {
        if (!myBall->move(width(), height(), *myRacket)) {
            myBall->reset(width());
            if (myBallsLeft > 0) {
                myBallsLeft--;
            } else {
                myIsStarted = false;
                QMessageBox::information(this, "Arcanoid", "Game Over!");
            }
        }
    }
    mySocket->writeDatagram(serialize().toString().toUtf8(), myDestinationAddress, myDestinationPort);
    update();
}

void BallDialog::paintEvent(QPaintEvent *) {
        QPainter p(this);
        p.setBrush(Qt::red);
        p.drawRect(myRacket->getX(), height() - myRacket->getHeight(), myRacket->getWidth(), myRacket->getHeight());
        p.setBrush(Qt::green);
        if (myIsStarted) {
            p.drawEllipse(QPoint(myBall->getX(), myBall->getY()), myBall->getXRadius(), myBall->getYRadius());
        }
}

void BallDialog::resizeEvent(QResizeEvent *) {
    myBall->recalculatePosition(width(), height());
    myRacket->recalculatePosition(width());
}

QDomDocument BallDialog::serialize() {
    QDomDocument resultDocument;
    QDomElement stateElement = resultDocument.createElement("state");
    stateElement.setAttribute("started", myIsStarted);
    stateElement.setAttribute("tableWidth", width());
    stateElement.setAttribute("ballsNumber", myBallsLeft);
    resultDocument.appendChild(stateElement);
    stateElement.appendChild(myBall->serialize());
    stateElement.appendChild(myRacket->serialize());
    return resultDocument;
}

void BallDialog::readDatagrams() {
    while (mySocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(mySocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        mySocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        if (sender == myDestinationAddress && senderPort == myDestinationPort) {
            processTheDatagram(datagram);
        }
    }
}

void BallDialog::processTheDatagram(const QByteArray &datagram) {
    QXmlSimpleReader reader;
    CommandHandler *commandHandler = new CommandHandler();
    reader.setContentHandler(commandHandler);
    QXmlInputSource inputXml;
    inputXml.setData(datagram);
    reader.parse(&inputXml);
    if (commandHandler->myDirection == 1) {
        moveRacketRight();
    } else if (commandHandler->myDirection == -1) {
        moveRacketLeft();
    } else if (commandHandler->myStarted) {
        startGame();
    }
}

BallDialog::CommandHandler::CommandHandler() {
    myStarted = false;
    myDirection = 0;
}

bool BallDialog::CommandHandler::startElement(const QString &, const QString &, const QString &name, const QXmlAttributes &) {
    if (name == "start") {
        myStarted = true;
    } else if (name == "moveRight") {
        myDirection = 1;
    } else if (name == "moveLeft") {
        myDirection = -1;
    }
    return true;
}

void BallDialog::startGame() {
    myBallsLeft = myBallsCount;
    myBall->reset(width());
    myIsStarted = true;
}

void BallDialog::moveRacketLeft() {
    myRacket->move(-std::min(myRacket->getX(), myRacketSpeed));
}

void BallDialog::moveRacketRight() {
    myRacket->move(std::min(width() - (myRacket->getX() + myRacket->getWidth()), myRacketSpeed));
}
