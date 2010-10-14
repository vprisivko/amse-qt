#include <QApplication>

#include "MagicBall.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	MagicBall *magicBall = new MagicBall();
	magicBall->show();
	
	return app.exec();
	
}
