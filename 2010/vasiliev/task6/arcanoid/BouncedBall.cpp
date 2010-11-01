#include <QPainter>
#include <QColor>
#include <Qt>
#include <QRect>
#include <QPointF>
#include <algorithm>

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

	myRacket.length = radius * 3;

	this->setWindowTitle("Bounced Ball by Vasiliev");

	this->setMinimumHeight(radius * 5);
	this->setMinimumWidth(radius * 5);

}

void Ball::timerEvent(QTimerEvent *e) {
	if (e->timerId() == myTimer_id) {

		myHeight = this->height();
		myWidth = this->width();

		if (myY > myHeight) {
			myY = myHeight;
		}
		if (myX > myWidth) {
			myX = myWidth;
		}

		if (myY > myRacket.yTopLeft) {
			emit gameover();
			killTimer(myTimer_id);
			myX = 100;
			myY = 100;
			myCurrRadiusX = 30;
			myCurrRadiusY = 30;
			
		}

		if (((myHeight - 5 < myY + myRadiusY) &&
		     (myX > myRacket.xTopLeft - 5) &&
		     (myX < myRacket.xTopLeft + myRacket.length + 5)) ||
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
			if ((myHeight - 5 < myY + myRadiusY) || (myY < myRadiusY / 2)) {
				if (myHeight - 5 < myY + myRadiusY) myCurrRadiusY -= myDirectionY;
				else myCurrRadiusY += myDirectionY;
				if (myCurrRadiusY < myRadiusY / 2) {
					myDirectionY = -myDirectionY;
				}
				if (myCurrRadiusY > myRadiusY) {
					isSticked = false;
				}
			}
			if ((myWidth - myX < myRadiusX) || (myX < myRadiusX / 2)) {
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

void Ball::moveLeft() {
	myRacket.xTopLeft -= 15;
	repaint();
}

void Ball::moveRight() {
	myRacket.xTopLeft += 15;
	repaint();
}

void Ball::start() {
	myTimer_id = startTimer(30);
	myX = 100;
	myY = 100;
	myDirectionX = 1;
	myDirectionY = 1,
	myRadiusX = 30;
	myRadiusY = 30;
	myCurrRadiusX = 30;
	myCurrRadiusY = 30;
	myHeight = 0;
	myWidth = 0;
	isSticked = false;
}

void Ball::resizeEvent(QResizeEvent *e) {
	myRacket.yTopLeft = e->size().height() - 5;
	repaint();
}

void Ball::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setBrush(Qt::blue);
	painter.drawEllipse(myX, myY, myCurrRadiusX, myCurrRadiusY);

	painter.setBrush(Qt::green);
	painter.drawRect(myRacket.xTopLeft, myRacket.yTopLeft, myRacket.length, 5);
}

