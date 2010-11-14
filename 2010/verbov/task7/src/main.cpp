#include <QApplication>
#include "TimerDialog.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	TimerDialog mainDialog;
	mainDialog.show();
	return app.exec();
}
