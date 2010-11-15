#include <QTest>
#include <QSignalSpy>

#include "TestTimer.h"

TestTimer::TestTimer():QObject() {
    timerDialog = new TimerDialog();
}

void TestTimer::testTimerPeriod1() {
    timerDialog->timerComboBox->setCurrentIndex( 0 );
    QTest::keyPress( timerDialog->periodLineEdit, Qt::Key_3 );
    QTest::keyPress( timerDialog->periodLineEdit, Qt::Key_0 );
    QTest::keyPress( timerDialog->periodLineEdit, Qt::Key_0 );
    QTest::mouseClick( timerDialog->setPeriodButton, Qt::LeftButton);

    QCOMPARE( (unsigned int) 300, timerDialog->timer1Period );
    QCOMPARE( (int) 300, timerDialog->periodLineEdit->text().toInt() );

    QTest::qWait( 350 );
    QCOMPARE( (int) 300, timerDialog->currentTime1Number->intValue() );
}


void TestTimer::testTimerPeriod2() {
    timerDialog->timerComboBox->setCurrentIndex( 1 );
    QTest::keyPress( timerDialog->periodLineEdit, Qt::Key_Backspace );
    QTest::keyPress( timerDialog->periodLineEdit, Qt::Key_Backspace );
    QTest::keyPress( timerDialog->periodLineEdit, Qt::Key_4 );
    QTest::keyPress( timerDialog->periodLineEdit, Qt::Key_2 );
    QTest::keyPress( timerDialog->periodLineEdit, Qt::Key_4 );
    QTest::mouseClick( timerDialog->setPeriodButton, Qt::LeftButton);

    QCOMPARE( (unsigned int) 3424, timerDialog->timer2Period );
    QCOMPARE( (int) 3424, timerDialog->periodLineEdit->text().toInt() );

    QTest::qWait( 3500 );
    QCOMPARE( (int) 3424, timerDialog->currentTime2Number->intValue() );
}


void TestTimer::testTimerComboBox() {
    QSignalSpy spy ( timerDialog->timerComboBox, SIGNAL( currentIndexChanged(int) ) );
    timerDialog->timerComboBox->setCurrentIndex(0);
    timerDialog->timerComboBox->setCurrentIndex(1);
    QCOMPARE( (int) 2, spy.count() );
}

void TestTimer::testStopTimers() {
    timerDialog->timerComboBox->setCurrentIndex( 0 );
    QTest::mouseClick( timerDialog->stopTimerButton, Qt::LeftButton);
    timerDialog->timerComboBox->setCurrentIndex( 1 );
    QTest::mouseClick( timerDialog->stopTimerButton, Qt::LeftButton);

    int time1 = timerDialog->currentTime1Number->intValue();
    int time2 = timerDialog->currentTime2Number->intValue();
    QTest::qWait( timerDialog->timer1Period + timerDialog->timer2Period );
    QCOMPARE( time1, timerDialog->currentTime1Number->intValue() );
    QCOMPARE( time2, timerDialog->currentTime2Number->intValue() );
}



