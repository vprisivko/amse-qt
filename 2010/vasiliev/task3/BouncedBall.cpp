#include <QPainter>
#include <QColor>
#include <Qt>
#include <QPointF>

#include "BouncedBall.h"

Ball::Ball(QWidget *parent,
		int radius,
		int directionX, int directionY): QWidget(parent),
	myX(100), myY(100),
	myDirectionX(directionX), myDirectionY(directionY),
	myRadiusX(radius), myRadiusY(radius),
	myCurrRadiusX(radius), myCurrRadiusY(radius),
	myHeight(0), myWidth(0),
	isSticked(false) {

	myTimer_id = startTimer(3);
	this->setWindowTitle("Bounced Ball by Vasiliev");
	
}

void Ball::setRadius(const int &radius) {
	this->myRadiusX = radius;
	this->myRadiusY = radius;
	this->myCurrRadiusX = radius;
	this->myCurrRadiusY = radius;
}

void Ball::setDirection(const int &directionX, const int &directionY) {
	this->myDirectionX = directionX;
	this->myDirectionY = directionY;
}

void Ball::timerEvent(QTimerEvent *e) {
	if (e->timerId() == myTimer_id) {

		myHeight = this->height();
		myWidth = this->width();
		if ((myHeight - myY < myRadiusY) ||
		    (myY < myRadiusY) ||
		    (myWidth - myX < myRadiusX) ||
		    (myX < myRadiusX)) {
			isSticked = true;
		} else {
			isSticked = false;
		}

		myX += myDirectionX;
		myY += myDirectionY;
		if (isSticked) {
			if ((myHeight - myY < myRadiusY) || (myY < myRadiusY)) {
				if (myHeight - myY < myRadiusY) myCurrRadiusY -= myDirectionY;
				else myCurrRadiusY += myDirectionY;
				if (myCurrRadiusY < myRadiusY / 2) {
					myDirectionY = -myDirectionY;
				}
				if (myCurrRadiusY > myRadiusY) {
					isSticked = false;
				}
			}
			if ((myWidth - myX < myRadiusX) || (myX < myRadiusX)) {
				if (myWidth - myX < myRadiusX) myCurrRadiusX -= myDirectionX;
				else myCurrRadiusX += myDirectionX;
				if (myCurrRadiusX < myRadiusX / 2) {
					myDirectionX = -myDirectionX;
				}
				if (myCurrRadiusX > myRadiusX) {
					isSticked = false;
				}
			}
		} else {
			myCurrRadiusX = myRadiusX;
			myCurrRadiusY = myRadiusY;
		}
		repaint();
	}
}

void Ball::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setBrush(Qt::blue);
	painter.drawEllipse(myX, myY, myCurrRadiusX, myCurrRadiusY);
}

