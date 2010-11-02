#include "Racket.h"

Racket :: Racket() {
	coordinates = QPointF(0, 0); 
	size = QSizeF(0, 0);
	windowWidth = 0; 
	windowHeight = 0; 
}
QPointF Racket :: getCoordinates() {
	return coordinates;
}
QRectF Racket :: getRectangle() {
	QRectF rectangle(coordinates, size);
	return rectangle;
}
QSizeF Racket :: getRacketSize() {
	return size;
}
QSizeF Racket :: getWindowSize() {
	return QSizeF(windowWidth, windowHeight);
}
void Racket :: setCoordinates(qreal x, qreal y) {
	coordinates.setX(x);
	coordinates.setY(y);
}
void Racket :: setCoordinateX(qreal x) {
	coordinates.setX(x);
}
void Racket :: setCoordinateY(qreal y) {
	coordinates.setY(y);
}
void Racket :: setWindowSize(qreal width, qreal height) {
	if (windowWidth != width || windowHeight != height) {
		setCoordinateX(coordinates.x()/(windowWidth/width));
		windowWidth = width;
		windowHeight = height;
		setSize();
		setCoordinateY(windowHeight - 30);
	}
}
void Racket :: setSize() {
	size.setWidth(windowWidth/4);
	size.setHeight(30);
}
