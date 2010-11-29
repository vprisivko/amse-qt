#include <QApplication>
#include "TimerDialog.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	TimerDialog dialog;
	dialog.show();
	return app.exec();
}
