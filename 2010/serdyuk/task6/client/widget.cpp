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

#include <QHBoxLayout>

Widget::Widget(QString port, QString address, QWidget *parent) : QWidget(parent) {
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
    mySocket->bind(QHostAddress(address), port.toInt());
}

