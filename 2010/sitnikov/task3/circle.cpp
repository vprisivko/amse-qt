#include <cstdlib>
#include <ctime>
#include <cmath>
#include <QVBoxLayout>
#include <QPainter>
#include "circle.h"


Circle::Circle(QWidget *parent) : QDialog(parent)
{
	setLayout(new QVBoxLayout());
	setMinimumSize(640, 480);

	const int r = 20;
	srand((int)time(0));
	circle_.radii = r;
	circle_.currX = rand() % (width() - 2 * r) + r;
	circle_.currY = rand() % (height() - 2 * r) + r;
	circle_.directX = rand() % 300;
	circle_.directY = rand() % 300;

	timerRedraw_ = startTimer(20);
	timerMove_ = startTimer(5);
}

void Circle::timerEvent(QTimerEvent* e)
{
	if(e->timerId() == timerMove_) {
		circle_.move();
	} else if(e->timerId() == timerRedraw_) {
		repaint();
	}
}

void Circle::paintEvent(QPaintEvent *e)
{
	circle_.maxWidth = e->rect().width();
	circle_.maxHeight = e->rect().height();
	QPainter paint(this);
	circle_.draw(&paint);
}


void Circle::circle_t::draw(QPainter *paint) const
{
	double width = 2.0 * radii;
	if(currX < radii) {
		width = 2.0 * currX;
	} else if(maxWidth - currX < radii) {
		width = 2.0 * (maxWidth - currX);
	}

	double height = 2.0 * radii;
	if(currY < radii) {
		height = 2.0 * currY;
	} else if(maxHeight - currY < radii) {
		height = 2.0 * (maxHeight - currY);
	}

	paint->setBrush(QColor(0, 100, 0));
	paint->drawEllipse(int(currX - width / 2.0), int(currY - height / 2.0), int(width), int(height));
}

void Circle::circle_t::move()
{
	if(currX < radii / 2.0)
		directX = -directX;
	if(currY < radii / 2.0)
		directY = -directY;

	if(maxWidth - currX < radii / 2.0)
		directX = -fabs(directX);
	if(maxHeight - currY < radii / 2.0)
		directY = -fabs(directY);

	currX += directX / 500.0;
	currY += directY / 500.0;
}
