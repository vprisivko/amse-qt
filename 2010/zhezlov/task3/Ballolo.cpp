#include <QVBoxLayout>
#include <QPainter>
#include <time.h>
#include <math.h>
#include "Ballolo.h"


Ballolo::Ballolo( QWidget* parent ):
									QDialog(parent){

	setLayout( new QVBoxLayout() );
	setMinimumSize( 400, 300 );

	qsrand( (uint)time(0) );

	b.r = 50;
	b.x = qrand() % 300 + 50;
	b.y = qrand() % 200 + 50;
	b.vx = qrand() % 200;
	b.vy = qrand() % 200;

	drawTimerId = startTimer( 25 );
	startTimer(1);

}

void Ballolo::timerEvent( QTimerEvent* e ){

	if ( e->timerId() == drawTimerId ){
		repaint();
	} else {
		moveBall();
	}

}


void Ballolo::paintEvent( QPaintEvent* e){

	QRect r = e->rect();

	QPainter painter(this);
	painter.setPen( Qt::NoPen );
	painter.setBrush( QColor(100, 100, 100) );
	painter.drawRect( e->rect() );

	double h,w;

	w = 2 * b.r;
	if ( b.x < b.r ) w = 2 * b.x;
	if ( r.width() - b.x < b.r ) w = 2* ( r.width() - b.x );

	h = 2 * b.r;
	if ( b.y < b.r ) h = 2 * b.y;
	if ( r.height() - b.y < b.r ) h = 2 * ( r.height() - b.y );

	painter.setBrush( QColor(180, 0, 0) );
	painter.drawEllipse( b.x - w/2, b.y - h/2, w, h);

}


void Ballolo::moveBall(){

	if ( b.x < b.r / 2 ) b.vx = -b.vx;
	if ( b.y < b.r / 2 ) b.vy = -b.vy;

	if ( rect().width() - b.x < b.r / 2 ) b.vx = - fabs( b.vx );
	if ( rect().height() - b.y < b.r / 2 ) b.vy = - fabs( b.vy );

	b.x += b.vx / 1000;
	b.y += b.vy / 1000;

}

