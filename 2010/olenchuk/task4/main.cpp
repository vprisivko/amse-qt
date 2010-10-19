#include <QApplication>
#include "MainWindow.h"

int main(int argv, char *argc[]) {
	QApplication app(argv, argc);
	MainWindow *mc = new MainWindow();
	mc->show();
	return app.exec();
}
