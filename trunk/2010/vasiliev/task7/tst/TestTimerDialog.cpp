#include "TestTimerDialog.h"

Tester::Tester(): QObject() {
	myTimerDialog = new TimerDialog();
}

Tester::~Tester() {
	delete myTimerDialog;
}

void Tester::testSignals() {
	myTimerDialog->myCBTimers->setCurrentIndex(0);
	QSignalSpy signalSpy(myTimerDialog->myCBTimers, SIGNAL(currentIndexChanged(int)));
	myTimerDialog->myCBTimers->setCurrentIndex(1);
	myTimerDialog->myCBTimers->setCurrentIndex(0);
	QCOMPARE(signalSpy.count(), 2);
}

void Tester::testButtons() {
	myTimerDialog->myCBTimers->setCurrentIndex(1);
	myTimerDialog->myEditInterval->setText("1000");
	QSignalSpy signalSpy(myTimerDialog->myButtonSet, SIGNAL(pressed()));
	QTest::mouseClick(myTimerDialog->myButtonSet, Qt::LeftButton);
	QCOMPARE(signalSpy.count(), 1);
}

void Tester::testSemantic() {
	myTimerDialog->myCBTimers->setCurrentIndex(0);
	myTimerDialog->myEditInterval->setText("100");
	int currentTime = myTimerDialog->myTicker1->intValue();
	QTest::mouseClick(myTimerDialog->myButtonSet, Qt::LeftButton);
	QTest::qWait(1050);
	QCOMPARE(myTimerDialog->myTicker1->intValue(), currentTime + 10);
}
