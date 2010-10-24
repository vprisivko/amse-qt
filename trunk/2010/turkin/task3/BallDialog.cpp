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

BallDialog::BallDialog(QWidget *parent): QDialog(parent),  DEFAULT_RADIUS(40) {
    srand( time(NULL) );

    curRadius = QSize(DEFAULT_RADIUS,DEFAULT_RADIUS);
    setMinimumSize(DEFAULT_RADIUS*2, DEFAULT_RADIUS*2);
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
    int rx = curRadius.width();
    int ry = curRadius.height();
    int windowHeight = height();
    int windowWidth = width();

    x += dx;
    y += dy;

    // if ball is out of window, take it to the window back!
    if (x > windowWidth - DEFAULT_RADIUS/2) {
        x = windowWidth - DEFAULT_RADIUS/2;
    }
    if (y > windowHeight - DEFAULT_RADIUS/2) {
        y = windowHeight - DEFAULT_RADIUS/2;
    }

    if (x < DEFAULT_RADIUS) {
        rx = x;
    } else {
        if (x + DEFAULT_RADIUS > windowWidth) {
                rx = windowWidth - x;
        } else {
                rx = DEFAULT_RADIUS;
        }
    }
    if (rx <= DEFAULT_RADIUS/2) {
        dx = -dx;
    }

    if (y < DEFAULT_RADIUS) {
        ry = y;
    } else {
        if (y + DEFAULT_RADIUS > windowHeight) {
                ry = windowHeight - y;  // if ball is out of window, take it to the window back!

        } else {
                ry = DEFAULT_RADIUS;
        }
    }
    if (ry <= DEFAULT_RADIUS/2) {
        dy = -dy;
    }

    //exception if ball is near both of edges
    if (rx < DEFAULT_RADIUS && ry < DEFAULT_RADIUS) {
        rx = DEFAULT_RADIUS;
        ry = DEFAULT_RADIUS;
    }


    coord = QPoint(x,y);
    curRadius = QSize(rx,ry);

    update();

}

void BallDialog::paintEvent(QPaintEvent*) {
	QPainter p(this);
        QRadialGradient gradient(coord,DEFAULT_RADIUS, coord-QPoint(5,5) );
	gradient.setColorAt(0.2, Qt::white);
	gradient.setColorAt(0.8, Qt::red);
	gradient.setColorAt(1, Qt::black);
	p.setBrush ( gradient  );
	p.setPen ( Qt::NoPen );
	p.drawEllipse( coord, curRadius.width(), curRadius.height() );
	

}
