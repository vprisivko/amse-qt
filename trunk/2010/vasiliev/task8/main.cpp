#include <QApplication>

#include "LoggerDialog.h"
#include "CalcDialog.h"

int main(int c, char **v) {
	QApplication app(c, v);

	CalcLog calcLogger;
	calcLogger.show();

	return app.exec();
}
