#include <QApplication>

#include "TimerDialog.h"

int main(int c, char **v) {
	QApplication app(c, v);
	TimerDialog d(NULL);
	d.show();
	return app.exec();
}
