#include <QTest>
#include <QSignalSpy>
#include "TimerDialogTest.h"

void TimerDialogTest::initTestCase() {
	timerDialog = new TimerDialog();
}

void TimerDialogTest::cleanupTestCase() {
	delete timerDialog;
}

void TimerDialogTest::testTimer1() {
	timerDialog->myComboBox->setCurrentIndex(1);

	QSignalSpy comboBoxSignalSpy(timerDialog->myComboBox, SIGNAL(currentIndexChanged(int)));
	timerDialog->myComboBox->setCurrentIndex(0);
	QCOMPARE(comboBoxSignalSpy.count(), 1);

	timerDialog->intervalEdit->setText("100");

	int valueBeforeStart = timerDialog->label1->text().mid(16).toInt();
	QTest::mouseClick(timerDialog->setButton, Qt::LeftButton);
	QTest::qWait(130);
	QCOMPARE(valueBeforeStart + 1, timerDialog->label1->text().mid(16).toInt());

	QTest::qWait(230);
	QCOMPARE(valueBeforeStart + 3, timerDialog->label1->text().mid(16).toInt());

	timerDialog->myComboBox->setCurrentIndex(1);
	timerDialog->myComboBox->setCurrentIndex(0);
	QCOMPARE(comboBoxSignalSpy.count(), 3);

	int valueBeforeStop = timerDialog->label1->text().mid(16).toInt();
	QTest::mouseClick(timerDialog->stopButton, Qt::LeftButton);
	QTest::qWait(230);
	QCOMPARE(valueBeforeStop, timerDialog->label1->text().mid(16).toInt());
}

void TimerDialogTest::testTimer2() {
	timerDialog->myComboBox->setCurrentIndex(0);
	QSignalSpy comboBoxSignalSpy(timerDialog->myComboBox, SIGNAL(currentIndexChanged(int)));
	timerDialog->myComboBox->setCurrentIndex(1);
	QCOMPARE(comboBoxSignalSpy.count(), 1);

	timerDialog->intervalEdit->setText("");
	QTest::keyClicks(timerDialog->intervalEdit, "100");
	QCOMPARE(timerDialog->intervalEdit->text(), QString("100"));
	int valueBeforeStart = timerDialog->label2->text().mid(16).toInt();
	QTest::mouseClick(timerDialog->setButton, Qt::LeftButton);
	QTest::qWait(130);
	QCOMPARE(valueBeforeStart + 1, timerDialog->label2->text().mid(16).toInt());
}

void TimerDialogTest::comboBoxTest() {
	timerDialog->myComboBox->setCurrentIndex(0);
	QCOMPARE(timerDialog->myComboBox->currentText(), QString("Timer 1"));

	QSignalSpy mySpy(timerDialog->myComboBox, SIGNAL(currentIndexChanged(int)));
	timerDialog->myComboBox->setCurrentIndex(1);

	QCOMPARE(mySpy.count(), 1);
	QCOMPARE(timerDialog->myComboBox->currentText(), QString("Timer 2"));
}

void TimerDialogTest::setButtonClickTest() {
	QSignalSpy mySpy(timerDialog->setButton,SIGNAL(clicked()));
	QTest::mouseClick(timerDialog->setButton, Qt::LeftButton);
	QCOMPARE(mySpy.count(), 1);
}

void TimerDialogTest::stopButtonClickTest() {
	QSignalSpy mySpy(timerDialog->stopButton,SIGNAL(clicked()));
	QTest::mouseClick(timerDialog->stopButton, Qt::LeftButton);
	QCOMPARE(mySpy.count(), 1);
}
