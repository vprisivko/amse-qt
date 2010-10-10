#include <QApplication>
#include "circle.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Circle c;
	c.show();
	return app.exec();
}
