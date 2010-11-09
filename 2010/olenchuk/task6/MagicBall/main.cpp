#include <QApplication>

#include "MagicBall.h"

int main(int argv, char *argc[]) {
	QApplication app(argv, argc);
	MagicBall magicBall;
	magicBall.show();

	return app.exec();
}
