#include <QTest>
#include <QSignalSpy>
#include "timertest.h"


TimerTest::TimerTest(QObject *parent /* = 0 */) : QObject(parent) { }

void TimerTest::initTestCase()
{
	dialog_ = new DialogWrapper();
}

void TimerTest::cleanupTestCase()
{
	delete dialog_;
}

void TimerTest::firstTimerTestCase()
{
	QCOMPARE(dialog_->trmTicker1_->intValue(), dialog_->count1_);

	int last = dialog_->count1_;
	QSignalSpy timerSpy(dialog_, SIGNAL(timerEventSignal()));

	dialog_->cbTimer_->setCurrentIndex(0);
	dialog_->txtValue_->setText("");
	Qt::Key period[] = { Qt::Key_1, Qt::Key_0, Qt::Key_0 };
	for(int i = 0, _i = sizeof(period) / sizeof(Qt::Key); i != _i; ++i)
		QTest::keyPress(dialog_->txtValue_, period[i]);

	QTest::mouseClick(dialog_->btnSet_, Qt::LeftButton);
	QTest::qWait(2500);
	QTest::mouseClick(dialog_->btnStop_, Qt::LeftButton);

	QVERIFY(timerSpy.count() != 0);
	QCOMPARE(last + timerSpy.count(), dialog_->count1_);
	QCOMPARE(dialog_->trmTicker1_->intValue(), dialog_->count1_);
}

void TimerTest::secondTimerTestCase()
{
	QCOMPARE(dialog_->trmTicker2_->intValue(), dialog_->count2_);

	int last = dialog_->count2_;
	QSignalSpy timerSpy(dialog_, SIGNAL(timerEventSignal()));

	dialog_->cbTimer_->setCurrentIndex(1);
	dialog_->txtValue_->setText("");
	Qt::Key period[] = { Qt::Key_3, Qt::Key_2, Qt::Key_1 };
	for(int i = 0, _i = sizeof(period) / sizeof(Qt::Key); i != _i; ++i)
		QTest::keyPress(dialog_->txtValue_, period[i]);

	QTest::mouseClick(dialog_->btnSet_, Qt::LeftButton);
	QTest::qWait(1500);
	QTest::mouseClick(dialog_->btnStop_, Qt::LeftButton);

	QVERIFY(timerSpy.count() != 0);
	QCOMPARE(last + timerSpy.count(), dialog_->count2_);
	QCOMPARE(dialog_->trmTicker2_->intValue(), dialog_->count2_);
}

void TimerTest::bothTimersTestCase()
{
	QCOMPARE(dialog_->trmTicker1_->intValue(), dialog_->count1_);
	QCOMPARE(dialog_->trmTicker2_->intValue(), dialog_->count2_);

	int last = dialog_->count1_ + dialog_->count2_;
	QSignalSpy timerSpy(dialog_, SIGNAL(timerEventSignal()));

	dialog_->cbTimer_->setCurrentIndex(0);
	dialog_->txtValue_->setText("42");
	QTest::mouseClick(dialog_->btnSet_, Qt::LeftButton);

	dialog_->cbTimer_->setCurrentIndex(1);
	dialog_->txtValue_->setText("13");
	QTest::mouseClick(dialog_->btnSet_, Qt::LeftButton);

	QTest::qWait(2500);
	QTest::mouseClick(dialog_->btnStop_, Qt::LeftButton);
	QTest::qWait(500);
	dialog_->cbTimer_->setCurrentIndex(0);
	QTest::mouseClick(dialog_->btnStop_, Qt::LeftButton);

	QVERIFY(timerSpy.count() != 0);
	QCOMPARE(last + timerSpy.count(), dialog_->count1_ + dialog_->count2_);
	QCOMPARE(dialog_->trmTicker1_->intValue(), dialog_->count1_);
	QCOMPARE(dialog_->trmTicker2_->intValue(), dialog_->count2_);
}
