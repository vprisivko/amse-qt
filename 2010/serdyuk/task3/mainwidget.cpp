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

Widget::Widget(QWidget *p) : QWidget(p) {
    myBallX = width() / 2;
    myBallY = height() / 2;
    myBallVx = rand() % 11 - 5;
    myBallVy = rand() % 11 - 5;
    startTimer(10);
}

void Widget::timerEvent(QTimerEvent *) {
    update();
}

void Widget::paintEvent(QPaintEvent *) {
    const int radius = 20;
    myBallX += myBallVx;
    myBallY += myBallVy;

    QPainter painter(this);
    QRadialGradient gradient(myBallX, myBallY, radius);
    gradient.setColorAt(1, QColor::fromRgbF(1, 0, 0, 1));
    gradient.setColorAt(0, QColor::fromRgbF(1, 1, 1, 1));
    painter.setBrush(gradient);
    painter.setPen(Qt::NoPen);

    int xRadius = radius;
    int yRadius = radius;
    if (myBallX - radius < 0) {
        xRadius = myBallX;
    } 
    if (myBallX + radius > width()) {
        xRadius = width() - myBallX;
    }
    if (myBallX - radius < -radius / 2 || myBallX + radius > width() + radius / 2) {
        myBallVx = -myBallVx;
    }
    if (myBallY - radius < 0) {
        yRadius = myBallY;
    }
    if (myBallY + radius > height()) {
        yRadius = height() - myBallY;
    }
    if (myBallY - radius < -radius / 2 || myBallY + radius > height() + radius / 2) {
        myBallVy = -myBallVy;
    }
    painter.drawEllipse(myBallX - xRadius, myBallY - yRadius, 2 * xRadius, 2 * yRadius);
}

