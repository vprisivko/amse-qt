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

        ball.r = 50;
        ball.x = qrand() % 300 + 50;
        ball.y = qrand() % 200 + 50;
        ball.vx = qrand() % 200;
        ball.vy = qrand() % 200;

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

        w = 2 * ball.r;
        if ( ball.x < ball.r ) w = 2 * ball.x;
        if ( r.width() - ball.x < ball.r ) w = 2* ( r.width() - ball.x );

        h = 2 * ball.r;
        if ( ball.y < ball.r ) h = 2 * ball.y;
        if ( r.height() - ball.y < ball.r ) h = 2 * ( r.height() - ball.y );

	painter.setBrush( QColor(180, 0, 0) );
        painter.drawEllipse( ball.x - w/2, ball.y - h/2, w, h);

}


void Ballolo::moveBall(){

        if ( ball.x < ball.r / 2 ) ball.vx = -ball.vx;
        if ( ball.y < ball.r / 2 ) ball.vy = -ball.vy;

        if ( rect().width() - ball.x < ball.r / 2 ) ball.vx = - fabs( ball.vx );
        if ( rect().height() - ball.y < ball.r / 2 ) ball.vy = - fabs( ball.vy );

        ball.x += ball.vx / 1000;
        ball.y += ball.vy / 1000;

}


void Ballolo::resizeEvent( QResizeEvent* e ){

    QSize widgetSize = e->size();

    if ( ball.x - ball.r/2 > widgetSize.width() ) ball.x = widgetSize.width() - ball.r/2;
    if ( ball.y - ball.r/2 > widgetSize.height() ) ball.y = widgetSize.height() - ball.r/2;

}
