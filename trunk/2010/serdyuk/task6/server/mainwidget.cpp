// =====================================================================================
// 
//       Filename:  mainwidget.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05.10.2010 22:23:41
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#include "mainwidget.h"

#include <QPainter>
#include <QDebug>

const static int WIDTH = 800;
const static int HEIGHT = 500;


Widget::Widget(QWidget *p) : QWidget(p) {
    myState = new State(WIDTH, HEIGHT, this);

    startTimer(10);
    setMaximumSize(WIDTH, HEIGHT);
    setMinimumSize(WIDTH, HEIGHT);

    mySocket = new QUdpSocket(this);
    int socketPort;
    for (int i = 10000; i < 65536; i++) {
        socketPort = i;
        if (mySocket->bind(QHostAddress::LocalHost, socketPort)) {
            break;
        }
    }
    setWindowTitle(QString("Port - %1").arg(socketPort));

    ready = false;

    connect(mySocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

void Widget::timerEvent(QTimerEvent *) {
    //QHostAddress address(myHttpAddress->text());
    //int port = myPort->text().toInt();
    //QByteArray array = myMessage->text().toAscii();
    if (ready) {
        QByteArray array = myState->write().toAscii();
        mySocket->writeDatagram(array.data(), array.size(), myAddress, myPort);
    }

    update();
}

void Widget::readPendingDatagrams() {
    while (mySocket->hasPendingDatagrams()) {
         QByteArray datagram;
         datagram.resize(mySocket->pendingDatagramSize());
         QHostAddress sender;
         quint16 senderPort;

         mySocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
         if (!ready) {
             myAddress = sender;
             myPort = senderPort;
             ready = true;
             qDebug() << sender << senderPort;
         } else {
             QDomDocument doc;
             doc.setContent(datagram);
             QDomElement docElem = doc.documentElement();
             //QDomNode n = docElem.firstChild();
             if (!docElem.isNull()) {
                 if (docElem.toElement().tagName() == "Action") {
                     myState->doAction(docElem.attribute("action"));
                 }
             }
         }

     }
}

void Widget::paintEvent(QPaintEvent *) {

    QPainter painter(this);
    QRadialGradient gradient(myState->getBall()->getX(), myState->getBall()->getY(), Ball::RADIUS);
    gradient.setColorAt(1, QColor::fromRgbF(1, 0, 0, 1));
    gradient.setColorAt(0, QColor::fromRgbF(1, 1, 1, 1));
    painter.setBrush(gradient);
    painter.setPen(Qt::NoPen);

    QPoint radius = myState->tick();

    int ballX = myState->getBall()->getX() - radius.x();
    int ballY = myState->getBall()->getY() - radius.y();

    painter.drawEllipse(ballX, ballY, 2 * radius.x(), 2 * radius.y());
    painter.drawRect(myState->getRacket()->getX(), height(), Racket::WIDTH, -Racket::HEIGHT);
}
    
void Widget::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Right) {
        myState->doAction("right");
    } else if (e->key() == Qt::Key_Left) {
        myState->doAction("left");
    } else if (e->key() == Qt::Key_Space) {
        myState->doAction("start");
    }
}

