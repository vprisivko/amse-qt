// =====================================================================================
// 
//       Filename:  widget.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  31.10.2010 23:31:46
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#include "widget.h"

#include "../server/state.h"

#include <QHBoxLayout>
#include <QApplication>
#include <QBuffer>
#include <QDebug>

Widget::Widget(QString address, QString port, QWidget *parent) : QWidget(parent) {
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    setLayout(buttonLayout);

    myLeftButton = new QPushButton("<-", this);
    myRightButton = new QPushButton("->", this);
    myStartButton = new QPushButton("Start", this);

    buttonLayout->addWidget(myLeftButton);
    buttonLayout->addWidget(myRightButton);
    buttonLayout->addWidget(myStartButton);

    myLeftButton->setDisabled(true);
    myRightButton->setDisabled(true);

    mySocket = new QUdpSocket(this);
    int i = 10000;
    while (!mySocket->bind(QHostAddress::LocalHost, i)) {
        ++i;
    }
    bool ok;
    myPort = port.toInt(&ok);
    if (ok) {
        QByteArray array(" ");
        myAddress = QHostAddress(address);
        mySocket->writeDatagram(array.data(), array.size(), myAddress, myPort);
    } else {
        qApp->quit();
    }

    connect(mySocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    connect(myLeftButton, SIGNAL(clicked()), this, SLOT(goLeft()));
    connect(myRightButton, SIGNAL(clicked()), this, SLOT(goRight()));
    connect(myStartButton, SIGNAL(clicked()), this, SLOT(start()));
}
    
void Widget::readPendingDatagrams() {
    while (mySocket->hasPendingDatagrams()) {
        QObject parent; 
        QByteArray datagram;
        datagram.resize(mySocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        mySocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        State *state = State::createInstance(new QXmlInputSource(new QBuffer(&datagram, &parent)), &parent);
        if (state->getCurrentState() == "begin" || state->getCurrentState() == "fall") {
            myStartButton->setEnabled(true);
        } else {
            myStartButton->setEnabled(false);
        }
        if (state->getCurrentState() == "run") {
            if (state->getRacket()->getX() <= 0) {
                myLeftButton->setEnabled(false);
            } else {
                myLeftButton->setEnabled(true);
            }
            if (state->getRacket()->getX() >= state->getFieldWidth() - Racket::WIDTH) {
                myRightButton->setEnabled(false);
            } else {
                myRightButton->setEnabled(true);
            }
        }
    }
}
    
void Widget::goRight() {
    QDomDocument doc;
    QDomElement root = doc.createElement("Action");
    root.setAttribute("action", "right");
    doc.appendChild(root);
    QByteArray array(doc.toString().toAscii());
    mySocket->writeDatagram(array.data(), array.size(), myAddress, myPort);
}
    
void Widget::goLeft() {
    QDomDocument doc;
    QDomElement root = doc.createElement("Action");
    root.setAttribute("action", "left");
    doc.appendChild(root);
    QByteArray array(doc.toString().toAscii());
    mySocket->writeDatagram(array.data(), array.size(), myAddress, myPort);
}
    
void Widget::start() {
    QDomDocument doc;
    QDomElement root = doc.createElement("Action");
    root.setAttribute("action", "start");
    doc.appendChild(root);
    QByteArray array(doc.toString().toAscii());
    mySocket->writeDatagram(array.data(), array.size(), myAddress, myPort);
}

void Widget::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_A) {
        goLeft();
    } else if (e->key() == Qt::Key_D) {
        goRight();
    } else if (e->key() == Qt::Key_S) {
        start();
    }
}
