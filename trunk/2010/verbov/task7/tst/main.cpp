#include <QApplication>
#include <QTest>
#include "TestTimers.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	TestTimers test;
	QTest::qExec(&test);
	return 0;
}
