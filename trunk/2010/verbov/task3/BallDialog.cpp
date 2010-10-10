#include <QPainter>
#include "BallDialog.h"

BallDialog::BallDialog(QWidget *parent, int x, int y, int dx, int dy, int rx, int ry, int time) : QDialog(parent) {
	myXCoord = x;
	myYCoord = y;
	myDx = dx;
	myDy = dy;
	myInitialXRadius = myXRadius = rx;
	myInitialYRadius = myYRadius = ry;
	startTimer(time);
}

void BallDialog::timerEvent(QTimerEvent *) {
	myXCoord += myDx;
	myYCoord += myDy;
	if (myXCoord - myXRadius < 0 || myXCoord + myXRadius > width()) {
		myDx = -myDx;
		myXRadius /= 2;
	} else if (myYCoord - myYRadius < 0 || myYCoord + myYRadius > height()) {
		myDy = -myDy;
		myYRadius /= 2;
	} else {
		if (myXRadius < myInitialXRadius) {
			myXRadius++;
		} else if (myYRadius < myInitialYRadius) {
			myYRadius++;
		}
	}
	update();
}

void BallDialog::paintEvent(QPaintEvent *) {
	QPainter p(this);
	p.setBrush(Qt::green);
	p.drawEllipse(QPoint(myXCoord, myYCoord), myXRadius, myYRadius);
}
