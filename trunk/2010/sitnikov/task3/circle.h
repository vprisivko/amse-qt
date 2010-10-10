#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include <QDialog>
#include <QPainter>
#include <QPaintEvent>


class Circle : public QDialog
{
	Q_OBJECT;

public:
	Circle(QWidget* parent = 0);

	virtual void timerEvent(QTimerEvent *);
	virtual void paintEvent(QPaintEvent *);

private:
	struct circle_t
	{
		double currX, currY;
		double directX, directY;
		double radii;
		int maxWidth, maxHeight;

		void move();
		void draw(QPainter *) const;
	};

private:
	int timerRedraw_;
	int timerMove_;
	circle_t circle_;
};

#endif
