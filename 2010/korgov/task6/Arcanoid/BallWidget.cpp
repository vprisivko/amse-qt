#include "BallWidget.h"

BallWidget::BallWidget(const QSize &size, QWidget *parent)
    : QWidget(parent),
    myBallAbsRadius(10),myBallStep(2),
    myBallDxDy(QSize(myBallStep,myBallStep)),
    myBallRadius(QSize(myBallAbsRadius,myBallAbsRadius)),
    myXSqueezeTimer(0),myYSqueezeTimer(0)
{
    this->setMinimumSize(size);
    myPlatformWidth = this->size().width()/3;
}

BallWidget::~BallWidget()
{

}

void BallWidget::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == myTimerId){
        if(myBallCoords.x() + 2*myBallRadius.width() > this->size().width()){
            myBallCoords.setX( this->size().width() - 2*myBallRadius.width());
            myBallDxDy.setWidth(-myBallStep);
            squeezeX();
        } else if(myBallCoords.x() < 0){
            myBallCoords.setX(0);
            myBallDxDy.setWidth(myBallStep);
            squeezeX();
        }

        if( (myBallCoords.y() + 2*myBallRadius.height()) > (this->size().height() - 10)
            && (myBallCoords.x() + myBallRadius.width()) <= (myPlatformX + myPlatformWidth)
            && myBallCoords.x() + myBallRadius.width() >= myPlatformX){
            myBallCoords.setY( this->size().height() - 2*myBallRadius.height() - 10);
            myBallDxDy.setHeight(-myBallStep);
            squeezeY();
        } else if( (myBallCoords.y() + 2*myBallRadius.height()) > this->size().height() ){
            stop();
        } else if(myBallCoords.y() < 0){

            myBallCoords.setY(0);
            myBallDxDy.setHeight(myBallStep);
            squeezeY();
        }

        myBallCoords.setX(myBallCoords.x() + myBallDxDy.width());
        myBallCoords.setY(myBallCoords.y() + myBallDxDy.height());

        //sendStatus();

    } else if (e->timerId() == myXSqueezeTimer){
        if(myXSqueezeTimerStatus < 0){
            myBallRadius.setWidth(myBallRadius.width() - 0.1*myBallAbsRadius);
            if(myBallRadius.width() <= myBallAbsRadius/2){
                myXSqueezeTimerStatus = 1;
            }
        } else if(myXSqueezeTimerStatus > 0){
            myBallRadius.setWidth(myBallRadius.width() + 0.1*myBallAbsRadius);
            if(myBallRadius.width() >= myBallAbsRadius){
                myXSqueezeTimerStatus = 0;
            }
        } else {
            killTimer(myXSqueezeTimer);
            myXSqueezeTimer = 0;
            myBallRadius.setWidth(myBallAbsRadius);
        }
    } else if (e->timerId() == myYSqueezeTimer){
        if(myYSqueezeTimerStatus < 0){
            myBallRadius.setHeight(myBallRadius.height() - 0.1*myBallAbsRadius);
            if(myBallRadius.height() <= myBallAbsRadius/2){
                myYSqueezeTimerStatus = 1;
            }
        } else if(myYSqueezeTimerStatus > 0){
            myBallRadius.setHeight(myBallRadius.height() + 0.1*myBallAbsRadius);
            if(myBallRadius.height() >= myBallAbsRadius){
                myYSqueezeTimerStatus = 0;
            }
        } else {
            killTimer(myYSqueezeTimer);
            myYSqueezeTimer = 0;
            myBallRadius.setHeight(myBallAbsRadius);
        }
    }
    this->repaint();
}

void BallWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(Qt::black);
    p.setBrush(Qt::yellow);
    p.drawRect(0,0,this->size().width(),this->size().height());
    p.setPen(Qt::black);
    p.setBrush(Qt::SolidPattern);
    p.drawEllipse(myBallCoords.x(),myBallCoords.y(),2*myBallRadius.width(),2*myBallRadius.height());
    p.setPen(Qt::SolidLine);
    p.setBrush(Qt::red);
    p.drawRect(myPlatformX,this->size().height()-10,myPlatformWidth,10);

}

void BallWidget::squeezeX(){
    if(myXSqueezeTimer != 0){
        killTimer(myXSqueezeTimer);
    }
    myXSqueezeTimerStatus = -1;
    myXSqueezeTimer = startTimer(50);
}

void BallWidget::squeezeY(){
    if(myYSqueezeTimer != 0){
        killTimer(myYSqueezeTimer);
    }
    myYSqueezeTimerStatus = -1;
    myYSqueezeTimer = startTimer(50);
}

void BallWidget::start(){
    myBallCoords.setX( qrand() % (this->size().width() - myBallRadius.width()) );
    myBallCoords.setY(qrand() % (this->size().height() - myBallRadius.height() - 30) );
    myPlatformX = (this->size().width() - myPlatformWidth)/2;
    myTimerId = startTimer(20);
}

void BallWidget::stop(){
    if(myTimerId != 0){
        killTimer(myTimerId);
    }
    emit gameOver();
}

void BallWidget::left(){
    if(myPlatformX > 0){
        myPlatformX -=myBallStep*10;
    }

}

void BallWidget::right(){
    if(myPlatformX+myPlatformWidth < this->size().width()){
        myPlatformX +=myBallStep*10;
    }
}
