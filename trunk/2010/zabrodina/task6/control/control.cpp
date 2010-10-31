#include "control.h"
#include <QHostAddress>
#include <QHBoxLayout>
#include<QDomDocument>
#include <iostream>

Control::Control(QHostAddress _destip, qint16 _destport, qint16 _myport, QWidget *parent)
    : QDialog(parent)
{
    this->destport = _destport;
    this->destip = _destip;
    this->myport = _myport;
    udpSocket = new QUdpSocket(this);
    if(!udpSocket->bind(myport)){
        printf("Enter another port.\n");
        exit(-1);
    }
    createWidgets();
}

Control::~Control()
{

}
void Control::createWidgets(){
    leftArrowButton = new QPushButton("<--",this);
    rightArrowButton = new QPushButton("-->",this);
    runButton = new QPushButton("Run New Game",this);
     this->setLayout(new QHBoxLayout(this));
    this->layout()->addWidget(leftArrowButton);
    this->layout()->addWidget(rightArrowButton);
    this->layout()->addWidget(runButton);
    connect(leftArrowButton,SIGNAL(pressed()),this,SLOT(sendLeftMessage()));
    connect(rightArrowButton,SIGNAL(pressed()),this,SLOT(sendRightMessage()));
    connect(runButton,SIGNAL(pressed()),this,SLOT(sendRunMessage()));
   connect(udpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
}

void Control::sendLeftMessage(){
    QByteArray datagram;
   QString inputMessage = "<command value=\"left\" />";
   datagram.append( inputMessage );
   udpSocket->writeDatagram(datagram,destip,destport);

}
void Control::sendRightMessage(){
    QByteArray datagram;
   QString inputMessage = "<command value=\"right\" />";
   datagram.append( inputMessage );
   udpSocket->writeDatagram(datagram,destip,destport);
}
void Control::sendRunMessage(){
    QByteArray datagram;
   QString inputMessage = "<command value=\"run\" />";
   datagram.append( inputMessage );
   udpSocket->writeDatagram(datagram,destip,destport);
}
void Control::readMessage(){

    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize( udpSocket->pendingDatagramSize() );
        QHostAddress senderHost;
        quint16 senderPort;
        udpSocket->readDatagram( datagram.data(), datagram.size(),&senderHost,&senderPort );
        QDomDocument doc;
        doc.setContent(datagram);
        cSt = createInstance(&doc);
        checkState();
   }


}
ControllState* Control::createInstance(QDomDocument *doc){
    ControllState *cSt= new ControllState();
    QDomElement state = doc->namedItem("State").toElement();
     cSt->livesleft = state.attribute("livesleft").toInt();
     cSt->widthScreen = state.attribute("width").toInt();

    QDomElement Rocket = state.namedItem("Rocket").toElement();
     cSt->xPosition = Rocket.attribute("xPositon").toInt();
     cSt->widthRocket = Rocket.attribute("widthRock").toInt();

    return cSt;
}

void Control::checkState(){
    if(cSt->xPosition <= 0){
        leftArrowButton->setEnabled(false);
    }
    else{
        leftArrowButton->setEnabled(true);
    }
   if(cSt->xPosition + cSt->widthRocket > cSt->widthScreen){
        rightArrowButton->setEnabled(false);
    }
   else{
       rightArrowButton->setEnabled(true);
    }
    if(cSt->livesleft == 0){
        runButton->setEnabled(true);
    }
    else{
        runButton->setEnabled(false);
    }

}
