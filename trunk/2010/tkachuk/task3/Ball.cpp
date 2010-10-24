#include <ctime>
#include <cstdlib>
#include <math.h>
#include <QPainter>
#include <QRect>
#include <QBrush>
#include <QColor>
#include <QPen>
#include <QTimer>

#include "Ball.h"

Ball::Ball(QWidget *parent) : QWidget(parent) {
	resize(400, 400);
	myRadius = 25;
	setMinimumSize(50, 50);
	myCoord = QPoint(width()/2, height()/2);
	
	srand(time(NULL));
	dx = dy = 0;
	while (dx == 0 && dy == 0) {
		dx = (rand()%5)*pow(-1, rand()%2);
		dy = (rand()%5)*pow(-1, rand()%2);
	}

	QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);
}

void Ball::computeParams() {
	int x = myCoord.x();
	int y = myCoord.y();
	int wth = width();
	int hgt = height();
	int rx, ry;

	x += dx;
	y += dy;

//ball param-s validation:
	if (dx == 0 && x > wth - myRadius) {
		dx -= 1;
	} else {
		if (x > wth - myRadius/2) {
			x = wth - myRadius/2;
		}
	}

	if (dy == 0 && y > hgt - myRadius) {
		dy -= 1;
	} else {
		if (y > hgt - myRadius/2) {
			y = hgt - myRadius/2;
		}
	}

//horizontal param-s:
	if (x < myRadius) {
		rx = x;		
	} else {
		if (x + myRadius > wth) {
			rx = wth - x;			
		} else {
			rx = myRadius;
		} 
	}
	if (rx <= myRadius/2) {
		dx = -dx;
	}

//vertical param-s:
	if (y < myRadius) {
		ry = y;		
	} else {
		if (y + myRadius > hgt) {
			ry = hgt - y;			
		} else {
			ry = myRadius;
		} 
	}
	if (ry <= myRadius/2) {
		dy = -dy;
	}

//if compression with dx and dy at the same time
	if (rx < myRadius*0.95 && ry < myRadius*0.95) {
		rx = myRadius*0.95;
		ry = myRadius*0.95;
	}

	myShape.setWidth(rx);
	myShape.setHeight(ry);

	myCoord.setX(x);
	myCoord.setY(y);
}

void Ball::paintEvent(QPaintEvent *) {
	QPainter p(this);
	p.setPen(Qt::NoPen);
	p.setBrush(Qt::black);

	computeParams();
	
	p.drawEllipse(myCoord, myShape.width(), myShape.height());
}
