#include<QtGui>
#include "BouncingBall.h"

BallWidget :: BallWidget( QWidget* parent, int myRadius, int velocityX, int velocityY ) :
	QWidget( parent ),
	myX( 100 ), myY( 100 ),
	myVelocityX( velocityX ), myVelocityY( velocityY ),
	myRadius( myRadius ),
	myCompressedRadiusX( myRadius ), myCompressedRadiusY( myRadius ),
	myHeight( 0 ), myWidth( 0 )
{
	this->setWindowTitle( "Bouncing Ball" );
	setMinimumSize( 4 * myRadius, 4 * myRadius );
	myTimerId = startTimer( 20 );
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

void BallWidget :: paintEvent( QPaintEvent* ) {
        QPainter painter( this );
        painter.setBrush( Qt::red );
	painter.drawEllipse( myX, myY, myCompressedRadiusX, myCompressedRadiusY );
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

     		if ( newX - myRadius < 0){
     			currRadiusX = newX;
     		}

     		if ( newY + myRadius > myHeight){
       			currRadiusY = myHeight - newY;
     		}

     		if ( newY - myRadius < 0){
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

void BallWidget :: resizeEvent( QResizeEvent* resizeEvent ){
	QSize widgetSize = resizeEvent->size();

    	if ( myX + myRadius  > widgetSize.width() ){ 
		myX = widgetSize.width() - myRadius/2;
	}
    	if ( myY + myRadius  > widgetSize.height() ){
		myY = widgetSize.height() - myRadius / 2;
	}
}
