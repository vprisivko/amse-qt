/*
 * BallWidget.cpp
 *
 *  Created on: 07.10.2010
 *      Author: Korgov Kirill
 */

#include "BallWidget.h"

BallWidget::BallWidget(QWidget* parent)
    : QWidget(parent), myBallAbsRadius(10),
      myBallXRadius(myBallAbsRadius), myBallYRadius(myBallAbsRadius),
      myBallStep(2),myBallDx(myBallStep),myBallDy(myBallStep),
      myXSqueezeTimer(0),myYSqueezeTimer(0)
{
    resize(300,300);
    myBallX = qrand() % (size().width() - myBallXRadius);
    myBallY = qrand() % (size().height() - myBallYRadius);
    myTimerId = startTimer(20);
}

BallWidget::~BallWidget()
{
}

void BallWidget::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == myTimerId){
        if(myBallX + 2*myBallXRadius > size().width()){
            myBallX = size().width() - 2*myBallXRadius;
            myBallDx=-myBallStep;
            squeezeX(true);
        } else if(myBallX < 0){
            myBallX = 0;
            myBallDx=myBallStep;
            squeezeX(true);
        }

        if(myBallY + 2*myBallYRadius > size().height()){

            myBallY = size().height() - 2*myBallYRadius;
            myBallDy=-myBallStep;
            squeezeY(true);
        } else if(myBallY < 0){

            myBallY = 0;
            myBallDy=myBallStep;
            squeezeY(true);
        }

        myBallX+=myBallDx;
        myBallY+=myBallDy;

    } else if (e->timerId() == myXSqueezeTimer){
        if(myXSqueezeTimerStatus < 0){
            myBallXRadius -= 0.1*myBallAbsRadius;
            if(myBallXRadius <= myBallAbsRadius/2){
                myXSqueezeTimerStatus = 1;
            }
        } else if(myXSqueezeTimerStatus > 0){
            myBallXRadius += 0.1*myBallAbsRadius;
            if(myBallXRadius >= myBallAbsRadius){
                myXSqueezeTimerStatus = 0;
            }
        } else {
            killTimer(myXSqueezeTimer);
            myXSqueezeTimer = 0;
            myBallXRadius = myBallAbsRadius;
        }
    } else if (e->timerId() == myYSqueezeTimer){
        if(myYSqueezeTimerStatus < 0){
            myBallYRadius -= 0.1*myBallAbsRadius;
            if(myBallYRadius <= myBallAbsRadius/2){
                myYSqueezeTimerStatus = 1;
            }
        } else if(myYSqueezeTimerStatus > 0){
            myBallYRadius += 0.1*myBallAbsRadius;
            if(myBallYRadius >= myBallAbsRadius){
                myYSqueezeTimerStatus = 0;
            }
        } else {
            killTimer(myYSqueezeTimer);
            myYSqueezeTimer = 0;
            myBallYRadius = myBallAbsRadius;
        }
    }
    this->repaint();
}

void BallWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(Qt::black);
    p.setBrush(Qt::SolidPattern);
    p.drawEllipse(myBallX,myBallY,2*myBallXRadius,2*myBallYRadius);
}

void BallWidget::squeezeX(bool ){
    if(myXSqueezeTimer != 0){
        killTimer(myXSqueezeTimer);
    }
    myXSqueezeTimerStatus = -1;
    myXSqueezeTimer = startTimer(50);
}

void BallWidget::squeezeY(bool ){
    if(myYSqueezeTimer != 0){
        killTimer(myYSqueezeTimer);
    }
    myYSqueezeTimerStatus = -1;
    myYSqueezeTimer = startTimer(50);
}
