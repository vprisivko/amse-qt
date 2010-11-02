#include "Ball.h"


Ball :: Ball() {
	defRad = 50;
	width = 300.0;
	height = 600.0;
	center = QPointF(width / 2, height / 2);
	radius = QPoint(1,1) * defRad;
	lives = 3;
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
int Ball :: getLives() {
	return lives;
}
void Ball :: setLives(int lives) {
	this->lives = lives;	
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





