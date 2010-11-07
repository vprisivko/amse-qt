#ifndef _BOUNCING_BALL_H_
#define _BOUNCING_BALL_H_

#include<QWidget>
#include<QEvent>
#include<QPaintEvent>
#include<QTimer>
#include <QResizeEvent>

const int WIDGET_HEIGHT = 400;
const int TIMER_VALUE = 30;
const int DEFAULT_RADIUS = 30;
const int X_BALL_COORDINTE = 100;
const int Y_BALL_COORDINTE = 50;
const int X_BALL_VELOCITY = 2;
const int Y_BALL_VELOCITY = 1;

const int ROCKET_HEIGHT = 5;
const int ROCKET_STEP = 15;

class BallWidget : public QWidget{
	Q_OBJECT;
    public:
        BallWidget( QWidget* parent = NULL );
    public:
        void setCoordinates( const int& x, const int& y);
	void setRadius( const int& radius );
	void setVelosity( const int& velocityX, const int& velocityY );
        void setRocket();
    public slots:
	void start();
	void moveLeft();
	void moveRight();
    public: signals:
	void gameover();

    private:
	void paintEvent( QPaintEvent* );
	void timerEvent( QTimerEvent* timerEvent );
	void resizeEvent( QResizeEvent* resizeEvent );

    public:
	struct Rocket{
		int xTopLeft;
		int yTopLeft;
		int length; 
	}myRocket;
	
    private:
	int myX, myY;
	int myVelocityX, myVelocityY;
	int myRadius;
	int myCompressedRadiusX, myCompressedRadiusY;
	int myHeight, myWidth;
	int myTimerId;

};

#endif
