#include <QSignalSpy>
#include <QTest>
#include "TestTimers.h"

TestTimers::TestTimers(QObject *parent) : QObject(parent) {
	myTimerDialog = new TimerDialog();
}

void TestTimers::test1() {
	myTimerDialog->myTimersList->setCurrentIndex(0);
	myTimerDialog->myTimerIntervalLineEdit->setText("500");
	QTest::mouseClick(myTimerDialog->mySetButton, Qt::LeftButton);
	QTest::qWait(2000);
	QCOMPARE(myTimerDialog->myFirstTimerValue, 3);
}

void TestTimers::test2() {
	int interval = 100;
	myTimerDialog->myTimersList->setCurrentIndex(1);
	myTimerDialog->myTimerIntervalLineEdit->setText(QString::number(interval));
	QTest::mouseClick(myTimerDialog->mySetButton, Qt::LeftButton);
	QTest::qWait(1000);
	QCOMPARE(myTimerDialog->mySecondTimerLabel->text(), QString("Timer 2: 9"));
}

void TestTimers::test3() {
	QSignalSpy setSpy(myTimerDialog->mySetButton, SIGNAL(pressed()));
	QSignalSpy stopSpy(myTimerDialog->myStopButton, SIGNAL(pressed()));
	QTest::mouseClick(myTimerDialog->mySetButton, Qt::LeftButton);
	QTest::mouseClick(myTimerDialog->myStopButton, Qt::LeftButton);
	QCOMPARE(setSpy.count(), 1);
	QCOMPARE(stopSpy.count(), 1);
}
