#include <QApplication>

#include "Dialog.h"

int main(int c, char **v) {
	QApplication app(c, v);
	Dialog d(NULL);
	d.show();
	return app.exec();
}
