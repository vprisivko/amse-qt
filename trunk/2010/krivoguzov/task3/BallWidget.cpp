#include <BallWidget.h>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <math.h>
#include <stdlib.h>

BallWidget::BallWidget(int x, QWidget *parent):QWidget(parent){
    BallRadius = x;
    qsrand(QTime::currentTime().msec());

    resize(350,350);
    myCurrentX = qrand() % height();
    myCurrentY = qrand() % width();

    mySpeed = 3 + qrand() % 2;
    myAngle = qrand() % 360;
    myDX = mySpeed * sin(myAngle);
    myDY = mySpeed * cos(myAngle);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(20);
}

void BallWidget::paintEvent(QPaintEvent *){
    double ellipseX, ellipseY;
    double shiftX, shiftY;
    ellipseX = ellipseY = BallRadius;
    shiftX = shiftY = 0;

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);

    myCurrentX += myDX;
    myCurrentY += myDY;

    //Right border
    if (( myCurrentX + BallRadius > width() ) && ( myCurrentX + BallRadius/2 < width() ) ){
        ellipseX = width()-myCurrentX;
        ellipseY = BallRadius*2 - (width()-myCurrentX);
    }

    if(myCurrentX + BallRadius/2 > width()){
        myDX *= -1;
        myCurrentX = width() - BallRadius/2;

        ellipseX = BallRadius / 2;
        ellipseY = BallRadius * 1.5;
    }
    //End right border

    //Left border
    if((myCurrentX < 0) && (myCurrentX + BallRadius/2 > 0)){
        shiftX = myCurrentX;
        ellipseX = BallRadius + myCurrentX;
        ellipseY = BallRadius - myCurrentX;

    }

    if(myCurrentX + BallRadius/2 < 0){
        shiftX = myCurrentX;
        myDX *= -1;
        myCurrentX = -BallRadius / 2;

        ellipseX = BallRadius / 2;
        ellipseY = BallRadius * 1.5;
    }
    //End left border

    //Bottom
    if (( myCurrentY + BallRadius > height() ) && ( myCurrentY + BallRadius/2 < height() ) ){
        ellipseY = height() - myCurrentY;
        ellipseX = BallRadius * 2 - (height() - myCurrentY);
    }

    if(myCurrentY + BallRadius / 2 > height()){
        myDY *= -1;
        myCurrentY = height() - BallRadius / 2;

        ellipseY = BallRadius / 2;
        ellipseX = BallRadius * 1.5;
    }
    //End bottom

    //Top
    if((myCurrentY < 0) && (myCurrentY + BallRadius / 2 > 0)){
        shiftY = myCurrentY;
        ellipseX = BallRadius - myCurrentY;
        ellipseY = BallRadius + myCurrentY;
    }

    if(myCurrentY + BallRadius / 2 < 0){
        shiftY = myCurrentY;
        myDY *= -1;
        myCurrentY = -BallRadius / 2;

        ellipseX = BallRadius * 1.5;
        ellipseY = BallRadius / 2;
    }
    //End top

    painter.drawEllipse(QRectF(myCurrentX - shiftX, myCurrentY - shiftY, ellipseX, ellipseY));
}
