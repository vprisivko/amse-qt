#include <QApplication>

#include "Arcanoid.h"

int main(int c, char **v) {
	QApplication app(c, v);
	Arcanoid a;
	a.show();
	return app.exec();
}
