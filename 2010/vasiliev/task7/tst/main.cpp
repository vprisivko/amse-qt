#include <QApplication>

#include "TestTimerDialog.h"

int main(int c, char **v) {
	QApplication app(c, v);
	Tester test;
	QTest::qExec(&test);
	return 0;
}
