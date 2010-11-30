#include <QApplication>
#include <QTest>
#include "TestCounter.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	TestCounter *testCounter = new TestCounter();
	QTest::qExec(testCounter);
	return app.exec();
}
