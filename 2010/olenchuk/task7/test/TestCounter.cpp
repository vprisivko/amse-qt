#include "TestCounter.h"

#include <QtTest>
#include <QtGui>

TestCounter :: TestCounter() : QObject() {
	counter = new Counter();
}
void TestCounter :: testComboBox() {
	QSignalSpy spy(counter->comboBox, SIGNAL(currentIndexChanged(int)));
	counter->comboBox->setCurrentIndex(1);
	counter->comboBox->setCurrentIndex(0);
	QCOMPARE((int) 2, spy.count());
}
void TestCounter :: testSetClicked() {
	counter->comboBox->setCurrentIndex(0);
	QTest::keyPress(counter->lineEdit, Qt::Key_4);
	QTest::keyPress(counter->lineEdit, Qt::Key_0);
	QTest::keyPress(counter->lineEdit, Qt::Key_0);
	QTest::mouseClick(counter->setButton, Qt::LeftButton);
	int time = counter->textLine->text().toInt();
	QTest::qWait(200);
	QCOMPARE(time, counter->textLine->text().toInt());
	QTest::qWait(300);
	QCOMPARE(++time, counter->textLine->text().toInt());
	counter->comboBox->setCurrentIndex(1);
	counter->lineEdit->clear();
	QTest::keyPress(counter->lineEdit, Qt::Key_4);
	QTest::keyPress(counter->lineEdit, Qt::Key_0);
	QTest::keyPress(counter->lineEdit, Qt::Key_0);
	QTest::keyPress(counter->lineEdit, Qt::Key_0);
	QTest::mouseClick(counter->setButton, Qt::LeftButton);
	time = counter->textLine->text().toInt();
	QTest::qWait(2000);
	QCOMPARE(time, counter->textLine->text().toInt());
	QTest::qWait(3000);
	QCOMPARE(++time, counter->textLine->text().toInt());
}
void TestCounter :: testStopClicked() {
	counter->comboBox->setCurrentIndex(0);
	counter->lineEdit->clear();
	counter->lineEdit->setText("13");
	counter->setClicked();
	QTest::mouseClick(counter->stopButton, Qt::LeftButton);
	int time = counter->textLine->text().toInt();
	QTest::qWait(13);
	QCOMPARE(time, counter->textLine->text().toInt());
	counter->comboBox->setCurrentIndex(1);
	counter->lineEdit->clear();
	counter->lineEdit->setText("400");
	counter->setClicked();
	time = counter->textLine->text().toInt();
	QTest::qWait(801);
	QVERIFY(counter->textLine->text().toInt() != time);
	QTest::mouseClick(counter->stopButton, Qt::LeftButton);
	time = counter->textLine->text().toInt();
	QTest::qWait(500);
	QCOMPARE(time, counter->textLine->text().toInt());
}
