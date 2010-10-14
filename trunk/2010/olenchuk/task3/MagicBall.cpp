#include <QtGui>
#include "MagicBall.h"

MagicBall :: MagicBall(QWidget *parent) : QDialog (parent) {
	
	qsrand(time(0));
	ball.defRad = 20;
	ball.center = QPoint(width() / 2,height() / 2);
	ball.radius = QPoint(1,1) * ball.defRad;
	x = 0;
	y = 0;
	x = qrand() % 4;
	y = qrand() % 4;

	if (x > 1) {
		x = 1;
	} else {
		x = -1;
	}
	if (y < 1) {
		y = 1;
	} else {
		y = -1;
	}
	ball.timer = startTimer(5);
	
	setWindowTitle(tr("Magic Ball"));
}

void MagicBall::timerEvent(QTimerEvent *event) {
	if (event->timerId() != ball.timer) {
		return;
	}
	if (ball.center.x() - ball.defRad <= rect().x()) {
		if (ball.radius.x() == ball.defRad/4) {
			x = -x;
		}
		if ((ball.radius.x() + x) <= ball.defRad) {
			ball.radius.setX(ball.radius.x() + x);
		}
	}
	if (ball.center.y() - ball.defRad <= rect().y()) {
		if (ball.radius.y() == ball.defRad/4) {
			y = -y;
		}
		if ((ball.radius.y() + y) <= ball.defRad) {
			ball.radius.setY(ball.radius.y() + y);
		}
	}
	if (ball.center.x() + ball.defRad >= width()) {
		if (ball.radius.x() == ball.defRad/4) {
			x = -x;
		}
		if ((ball.radius.x() - x) <= ball.defRad) {
			ball.radius.setX(ball.radius.x() - x);
		}
	}
	if (ball.center.y() + ball.defRad >= height()) {
		if (ball.radius.y() == ball.defRad/4) {
			y = -y;
		}
		if ((ball.radius.y() - y) <= ball.defRad) {
			ball.radius.setY(ball.radius.y() - y);
		}
	}
	
	ball.center.setX(ball.center.x() + x);
	ball.center.setY(ball.center.y() + y);
	update();
}
void MagicBall :: paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	//painter.setRenderHint(QPainter::NonCosmeticDefaultPen, true);
	painter.setPen(Qt::blue);
    	painter.setBrush(Qt::black);
    	painter.drawEllipse(ball.center,ball.radius.x(),ball.radius.y());
    	painter.end();
}
