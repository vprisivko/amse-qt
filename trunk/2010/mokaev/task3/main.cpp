#include<QApplication>

#include "BouncingBall.h"

int main( int argc, char* argv[] ){
	QApplication app( argc, argv );
	int radius = 50;
	int velocityX = 1, velocityY = -2;
	BallWidget bouncingBall( NULL, radius, velocityX, velocityY );
	bouncingBall.show();
	return app.exec();
}
