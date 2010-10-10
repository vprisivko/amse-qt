#ifndef _BALL_H_
#define _BALL_H_

#include <QWidget>
#include <QTimerEvent>
#include <QPaintEvent>
#include <QPoint>
#include <QSize>

class Ball : public QWidget {
	Q_OBJECT;

	public:
		Ball(QWidget *parent = NULL);
		virtual void timerEvent(QTimerEvent *);
		virtual void paintEvent(QPaintEvent *);

	private:
		int myRadius;
		QPoint myCoord;
		QSize myShape;		
        int dx, dy;
};

#endif
