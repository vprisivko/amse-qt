#ifndef _BALL_H_
#define _BALL_H_

#include <QWidget>
#include <QPaintEvent>
#include <QPoint>
#include <QSize>

class Ball : public QWidget {
	Q_OBJECT;

	public:
		Ball(QWidget *parent = NULL);
		virtual void paintEvent(QPaintEvent *);

	private:
		void computeParams();

	private:
		int myRadius;
		QPoint myCoord;
		QSize myShape;
        int dx, dy;
};

#endif
