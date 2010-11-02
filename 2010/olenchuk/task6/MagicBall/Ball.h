#ifndef BALL_H
#define BALL_H

#include <QtGlobal> 
#include <QPointF>
#include <QPoint>

class Ball {
	
	public:
		Ball();
	
	public:
		void setCenterX(qreal x);
		void setCenterY(qreal y);
		void setWindowSize(qreal width, qreal height);
		void setRadiusX(int x);
		void setRadiusY(int y);
		void setLives(int lives);
		int getLives();
		QPointF getCenter();
		QPoint getRadius();
		qreal getDefRad();
		qreal getWidth();
		qreal getHeight();
	
	private:
		qreal width;
		qreal height;
		qreal defRad;
		QPointF center;
		QPoint radius;
		int lives;

};


#endif
