#include <ctime>
#include <cstdlib>
#include <math.h>
#include <QPainter>
#include <QRect>
#include <QBrush>
#include <QColor>
#include <QPen>

#include "Ball.h"

Ball::Ball(QWidget *parent) : QWidget(parent) {
	myRadius = 25;
	myShape = QSize(myRadius, myRadius);
	myCoord = QPoint(width()/2, height()/2);
	
	srand(time(NULL));
	dx = dy = 0;
	while (dx == 0 && dy == 0) {
		dx = (rand()%5)*pow(-1, rand()%2);
		dy = (rand()%5)*pow(-1, rand()%2);
	}

	startTimer(10);	
}

void Ball::timerEvent(QTimerEvent *) {
	int x = myCoord.x(), y = myCoord.y();
	int rx,ry;

	x += dx;
	y += dy;	

	rx = ry = myRadius;
	
	if (y + myRadius > height()) {
		ry -=  y + myRadius - height();
	} else if (y - myRadius < 0) {
		ry -= - (y - myRadius);
	} 

	if (x + myRadius > width()) {
		rx -= x + myRadius - width();
	} else if (x - myRadius < 0) {
		rx -= - (x - myRadius);
	}

	if (rx != myRadius && ry != myRadius) {
		dy = -dy;
		dx = -dx;
	}

	if (ry < myRadius / 2) {
		dy = -dy;
	}
	if (rx < myRadius / 2) {
		dx = -dx;
	}

	myCoord = QPoint(x,y);
	myShape = QSize(rx,ry);

   	update();
}

void Ball::paintEvent(QPaintEvent *) {
	QPainter p(this);
	p.setPen(Qt::black);
	p.setBrush(Qt::SolidPattern);
	p.drawEllipse( myCoord, myShape.width(), myShape.height() );
}
