#include <QApplication>

#include "Counter.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	Counter *counter = new Counter();
	counter->show();
	return app.exec();
}
