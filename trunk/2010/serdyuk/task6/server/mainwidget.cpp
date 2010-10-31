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

const static int WIDTH = 800;
const static int HEIGHT = 500;

Widget::Widget(QWidget *p) : QWidget(p) {
    myState = new State(WIDTH, HEIGHT, this);

    myState->changeState("run");

    startTimer(10);
    setMaximumSize(WIDTH, HEIGHT);
    setMinimumSize(WIDTH, HEIGHT);

    mySocket = new QUdpSocket(this);
    for (int i = 10000; i < 65536; i++) {
        myPort = i;
        if (mySocket->bind(QHostAddress::LocalHost, myPort)) {
            break;
        }
    }
    QHostAddress address = QHostAddress::LocalHost;
    setWindowTitle(QString("Port - %1").arg(myPort));
}

void Widget::timerEvent(QTimerEvent *) {
    update();
}

void Widget::paintEvent(QPaintEvent *) {

    QPainter painter(this);
    QRadialGradient gradient(myState->getBall()->getX(), myState->getBall()->getY(), myState->BALL_RADIUS);
    gradient.setColorAt(1, QColor::fromRgbF(1, 0, 0, 1));
    gradient.setColorAt(0, QColor::fromRgbF(1, 1, 1, 1));
    painter.setBrush(gradient);
    painter.setPen(Qt::NoPen);

    myState->tick();

    int ballX = myState->getBall()->getX() - myState->BALL_RADIUS;
    int ballY = myState->getBall()->getY() - myState->BALL_RADIUS;

    painter.drawEllipse(ballX, ballY, 2 * myState->BALL_RADIUS, 2 * myState->BALL_RADIUS);
}

