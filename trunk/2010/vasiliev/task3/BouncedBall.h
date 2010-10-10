#ifndef _BALL_H_
#define _BALL_H_

#include <QWidget>
#include <QEvent>
#include <QPaintEvent>
#include <QTimer>

class Ball: public QWidget {

Q_OBJECT;

public:
	Ball(QWidget *parent = NULL, int radius = 0, int directionX = 0, int directionY = 0);

	void setRadius(const int &);
	void setDirection(const int &, const int &);

	void paintEvent(QPaintEvent *);
	void timerEvent(QTimerEvent *);

public slots:
	

private:
	int myTimer_id;
	int myX, myY;
	int myDirectionX, myDirectionY;
	int myRadiusX;
	int myRadiusY;
	int myCurrRadiusX, myCurrRadiusY;
	int myHeight, myWidth;
	bool isSticked;

};

#endif // _BALL_H_
