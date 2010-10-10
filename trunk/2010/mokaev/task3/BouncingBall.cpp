#include<QtGui>
#include "BouncingBall.h"

BallWidget :: BallWidget( QWidget* parent, int radius, int velocityX, int velocityY ) :
	QWidget( parent ),
	myX( 100 ), myY( 100 ),
	myVelocityX( velocityX ), myVelocityY( velocityY ),
	myRadius( radius ),
	myCurrRadiusX( radius ), myCurrRadiusY( radius ),
	myHeight( 0 ), myWidth( 0 ),
	isKicked( false ) 
{
	this->setWindowTitle( "Bouncing Ball" );
	myTimerId = startTimer( 10 );
}


void BallWidget :: setRadius( const int& radius ) {
	this->myRadius = radius;
	this->myCurrRadiusX = radius;
	this->myCurrRadiusY = radius;
}

void BallWidget :: setVelosity( const int& velocityX, const int& velocityY ) {
	this->myVelocityX = velocityX;
	this->myVelocityY = velocityY;
}

void BallWidget :: paintEvent( QPaintEvent* ) {
	QPainter painter( this );
	painter.setBrush( Qt::red );
	painter.drawEllipse( myX, myY, myCurrRadiusX, myCurrRadiusY );
}

void BallWidget :: timerEvent( QTimerEvent* timerEvent ) {
	if ( timerEvent->timerId() == myTimerId ) {

		myHeight = this->height();
		myWidth = this->width();
		if ( ( myHeight - myY < myRadius) || ( myY < myRadius ) || ( myWidth - myX < myRadius ) || ( myX < myRadius ) ) {
			isKicked = true;
		} else {
			isKicked = false;
		}

		myX += myVelocityX;
		myY += myVelocityY;
		if ( isKicked ) {
			if ( ( myHeight - myY < myRadius ) || ( myY < myRadius ) ) {
				if ( myHeight - myY < myRadius ){
					myCurrRadiusY -= myVelocityY;
				}else{ 
					myCurrRadiusY += myVelocityY;
				}
				if ( myCurrRadiusY < myRadius / 2 ) {
					myVelocityY = -myVelocityY;
				}
				if (myCurrRadiusY > myRadius) {
					isKicked = false;
				}
			}
			if ( ( myWidth - myX < myRadius ) || ( myX < myRadius ) ) {
				if ( myWidth - myX < myRadius ){ 
					myCurrRadiusX -= myVelocityX;
				}else{
					myCurrRadiusX += myVelocityX;
				}
				if ( myCurrRadiusX < myRadius / 2 ) {
					myVelocityX = -myVelocityX;
				}
				if ( myCurrRadiusX > myRadius ) {
					isKicked = false;
				}
			}
		} else {
			myCurrRadiusX = myRadius;
			myCurrRadiusY = myRadius;
		}
		repaint();
	}
}
