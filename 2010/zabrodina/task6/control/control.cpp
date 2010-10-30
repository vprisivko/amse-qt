#include "control.h"
#include <QHostAddress>
#include <QHBoxLayout>
Control::Control(int _port, QWidget *parent)
    : QDialog(parent)
{
    this->port = _port;
    createWidgets();
    ballSocket = new QUdpSocket(this);
    if(!udpSocket->bind(port)){
        printf("Enter another port.\n");
        exit(-1);
    }
}

Control::~Control()
{

}
void Control::createWidgets(){
    leftArrowButton = new QPushButton("<--",this);
    rightArrowButton = new QPushButton("-->",this);
    runButton = new QPushButton("Run",this);
    this->setLayout(new QHBoxLayout(this));
    this->layout()->addWidget(leftArrowButton);
    this->layout()->addWidget(rightArrowButton);
    this->layout()->addWidget(runButton);
}
