#include <ctime>
#include <cstdlib>

#include <QDebug>
#include <QPainter>
#include <QRect>
#include <QBrush>
#include <QColor>
#include <QPen>
#include <QRadialGradient>

#include "BallDialog.h"

BallDialog::BallDialog(QWidget *parent): QDialog(parent) {
	srand( time(NULL) );

	initRadius = 20;
	curRadius = QSize(initRadius,initRadius);
	coord = QPoint( width() / 2 , height() / 2);
	
	dx = dy = 0;
	while (dx == 0 && dy == 0) {
		dx = rand() % 4 - 2;
		dy = rand() % 4 - 2;
	}

	startTimer(10);
}

void BallDialog::timerEvent(QTimerEvent*) {
  	
 	int x = coord.x(), y = coord.y();
	int rx,ry;
	
	//moving
	x += dx;
	y += dy;	

	//collapsing ball
	rx = ry = initRadius;
	
	if ( y + initRadius > height() ) {
		ry -=  y + initRadius - height();
	} else if ( y - initRadius < 0 ) {
		ry -= - (y - initRadius);
	} 

	if ( x + initRadius > width() ) {
		rx -= x + initRadius - width();
	} else if ( x - initRadius < 0 ) {
		rx -= - ( x - initRadius );
	}
	
	//exception if ball is near both of edges
	//don't wait for it's collapsing, push off
	if (rx != initRadius && ry != initRadius) {
		dy = -dy;
		dx = -dx;
	}

	//when ball is collapsed enough, push off from wall
	if ( ry < initRadius / 2 ) {
		dy = -dy;
	}
	if ( rx < initRadius / 2 ) {
		dx = -dx;
	}

	coord = QPoint(x,y);
	curRadius = QSize(rx,ry);

   	update();

}

void BallDialog::paintEvent(QPaintEvent*) {
	QPainter p(this);
	QRadialGradient gradient(coord,initRadius, coord-QPoint(5,5) );
	gradient.setColorAt(0.2, Qt::white);
	gradient.setColorAt(0.8, Qt::red);
	gradient.setColorAt(1, Qt::black);
	p.setBrush ( gradient  );
	p.setPen ( Qt::NoPen );
	p.drawEllipse( coord, curRadius.width(), curRadius.height() );
	

}
