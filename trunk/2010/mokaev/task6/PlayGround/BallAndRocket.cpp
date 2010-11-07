#include <QtGui>
#include "BallAndRocket.h"

BallWidget :: BallWidget( QWidget* parent ) : QWidget( parent ), myHeight( 0 ), myWidth( 0 )
{
    setMinimumSize( 5 * DEFAULT_RADIUS, 5 * DEFAULT_RADIUS );
    this->setFixedHeight( WIDGET_HEIGHT );
    setCoordinates( X_BALL_COORDINTE, Y_BALL_COORDINTE );
    setRadius( DEFAULT_RADIUS );
    setRocket();
}

void BallWidget :: setCoordinates( const int& x, const int& y ){
    this->myX = x;
    this->myY = y;
}

void BallWidget :: setRadius( const int& myRadius ) {
    this->myRadius = myRadius;
    this->myCompressedRadiusX = myRadius;
    this->myCompressedRadiusY = myRadius;
}

void BallWidget :: setVelosity( const int& velocityX, const int& velocityY ) {
    this->myVelocityX = velocityX;
    this->myVelocityY = velocityY;
}

void BallWidget :: setRocket(){
    myRocket.xTopLeft = width() / 2;
    myRocket.yTopLeft = height() - 20;
    myRocket.length = 3 * DEFAULT_RADIUS;
}

void BallWidget :: paintEvent( QPaintEvent* ) {
    QPainter painter( this );
    painter.setBrush( Qt::red );
    painter.drawEllipse( myX, myY, myCompressedRadiusX, myCompressedRadiusY );
	
    painter.setBrush( Qt::blue );
    painter.drawRect( myRocket.xTopLeft, myRocket.yTopLeft, myRocket.length, ROCKET_HEIGHT );
}

void BallWidget :: timerEvent( QTimerEvent* timerEvent ) {
	if ( timerEvent->timerId() == myTimerId ) {
		myHeight = this->height();
		myWidth = this->width();
		
		int newX = myX;
    		int newY = myY;
     		newX += myVelocityX;
     		newY += myVelocityY;

     		int currRadiusX = myRadius;
     		int currRadiusY = myRadius;

     		if ( newX + myRadius > myWidth ){
       			currRadiusX = myWidth - newX;
     		}

                if ( newX - myRadius < 0 ){
     			currRadiusX = newX;
     		}

                if( ( newY + myRadius > myRocket.yTopLeft ) && ( newX + myRadius > myRocket.xTopLeft ) && ( newX < myRocket.xTopLeft + myRocket.length ) ){
			currRadiusY = myRocket.yTopLeft - newY;
		}

                if ( newY > myHeight ){
			emit gameover();
                        killTimer( myTimerId );
                        setRadius( DEFAULT_RADIUS );
                        setCoordinates( X_BALL_COORDINTE, Y_BALL_COORDINTE );
                        repaint();
                        return;
     		}

                if ( newY - myRadius < 0 ){
       			currRadiusY = newY;
     		}

     		if ( currRadiusX < myRadius / 2 ){
       			myVelocityX = -myVelocityX;
     		}

     		if ( currRadiusY < myRadius / 2 ){
       			myVelocityY = -myVelocityY;
     		}

     		myX = newX;
     		myY = newY;
     		myCompressedRadiusX = currRadiusX;
     		myCompressedRadiusY = currRadiusY;

		repaint();
	}
}


void BallWidget :: moveLeft() {

    if( myRocket.xTopLeft - ROCKET_STEP >= 0 ){
        myRocket.xTopLeft -= ROCKET_STEP;
    }
    repaint();
}

void BallWidget :: moveRight() {
    if( myRocket.xTopLeft + myRocket.length + ROCKET_STEP <= this->width() ){
        myRocket.xTopLeft += ROCKET_STEP;
    }
    repaint();
}

void BallWidget :: start() {

        myTimerId = startTimer( TIMER_VALUE );
        setCoordinates( X_BALL_COORDINTE, Y_BALL_COORDINTE );
        setRadius( DEFAULT_RADIUS );
        setVelosity( X_BALL_VELOCITY, Y_BALL_VELOCITY );

        setRocket();

        myHeight = 0;
	myWidth = 0;

}

void BallWidget :: resizeEvent( QResizeEvent* resizeEvent ){
	QSize widgetSize = resizeEvent->size();

    	if ( myX + myRadius  > widgetSize.width() ){ 
		myX = widgetSize.width() - myRadius / 2;
	}
    	if ( myY + myRadius  > widgetSize.height() ){
		myY = widgetSize.height() - myRadius / 2;
	}
}
