#ifndef RACKET_H
#define RACKET_H

#include <QPointF>
#include <QRectF>
#include <QSizeF>

class Racket {

	public:
		Racket();
	
	public:
		QPointF getCoordinates();
		QRectF getRectangle();
		QSizeF getRacketSize();
		QSizeF getWindowSize();
		void setCoordinates(qreal x, qreal y);
		void setCoordinateX(qreal x);
		void setCoordinateY(qreal y);
		void setWindowSize(qreal width, qreal height);
		void setSize();
		
		
	private:
		QPointF coordinates;
		QSizeF size;
		qreal windowWidth; 
		qreal windowHeight; 

};


#endif
