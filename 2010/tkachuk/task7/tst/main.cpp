#include <QApplication>
#include <QTest>
#include "TimerDialogTest.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);

	TimerDialogTest *testObject = new TimerDialogTest();
	QTest::qExec(testObject);

	return 0;
}
