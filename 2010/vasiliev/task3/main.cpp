#include <QApplication>

#include "BouncedBall.h"

int main(int c, char **v) {
	QApplication app(c, v);
	int radius = 30, directionX = 1, directionY = 1;
	Ball b(NULL, radius, directionX, directionY);
	b.show();
	return app.exec();
}
