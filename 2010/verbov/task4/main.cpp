#include <QApplication>
#include "LogWindow.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	LogWindow window;
	window.show();
	return app.exec();
}
