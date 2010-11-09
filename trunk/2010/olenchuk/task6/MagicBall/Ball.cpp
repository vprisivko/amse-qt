#include "Ball.h"


Ball :: Ball() {
	defRad = 50;
	width = 0;
	height = 0;
	center = QPointF(0, 0);
	radius = QPoint(1,1) * defRad;
}
QPointF Ball :: getCenter() {
	return center;
}
QPoint Ball :: getRadius() {
	return radius;
}
qreal Ball :: getDefRad() {
	return defRad;
}
qreal Ball :: getWidth() {
	return width;
}
qreal Ball :: getHeight() {
	return height;
}
void Ball :: setCenterX(qreal x) {
	center.setX(x);
}
void Ball :: setCenterY(qreal y) {
	center.setY(y);
}
void Ball :: setRadiusX(int x) {
	radius.setX(x);
}
void Ball :: setRadiusY(int y) {
	radius.setY(y);
}
void Ball :: setWindowSize(qreal width, qreal height) {
	this->width = width;
	this->height = height;
}





