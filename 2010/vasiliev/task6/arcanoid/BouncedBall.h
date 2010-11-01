#ifndef _BALL_H_
#define _BALL_H_

#include <QWidget>
#include <QEvent>
#include <QPaintEvent>
#include <QTimer>
#include <QPushButton>
#include <QResizeEvent>

class Arcanoid;

struct Racket{
	int xTopLeft;
	int yTopLeft;
	int length; 
};

class Ball: public QWidget {

Q_OBJECT;

public:
	Ball(QWidget *parent = NULL, int radius = 0, int directionX = 0, int directionY = 0);

	void paintEvent(QPaintEvent *);
	void resizeEvent(QResizeEvent *);
	void timerEvent(QTimerEvent *);

public slots:
	void start();
	void moveLeft();
	void moveRight();

public: signals:
	void gameover();

private:
	friend class Arcanoid;
	int myTimer_id;
	int myX, myY;
	int myDirectionX, myDirectionY;
	int myRadiusX;
	int myRadiusY;
	int myCurrRadiusX, myCurrRadiusY;
	int myHeight, myWidth;
	Racket myRacket;
	bool isSticked;

};

#endif // _BALL_H_
