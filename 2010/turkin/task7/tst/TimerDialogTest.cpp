#include <QTest>
#include <QSignalSpy>

#include "TimerDialogTest.h"

TimerDialogTest::TimerDialogTest() {
    myDialog = new Dialog();
}

TimerDialogTest::~TimerDialogTest() {
     delete myDialog;
}


void TimerDialogTest::testTimerOnOff() {

    myDialog->leInterval->setText("1");

    myDialog->cbChooseTimer->setCurrentIndex(0);
    myDialog->setTimer();
    myDialog->cbChooseTimer->setCurrentIndex(1);
    myDialog->setTimer();
    QCOMPARE(myDialog->isTimerOn[0],true);
    QCOMPARE(myDialog->isTimerOn[1],true);

    myDialog->stopTimer();
    QCOMPARE(myDialog->isTimerOn[0],true);
    QCOMPARE(myDialog->isTimerOn[1],false);

    myDialog->cbChooseTimer->setCurrentIndex(0);
    myDialog->stopTimer();

    QCOMPARE(myDialog->isTimerOn[0],false);
    QCOMPARE(myDialog->isTimerOn[1],false);

}

void TimerDialogTest::testSignalIntervalChange(){
    QSignalSpy s(myDialog->leInterval,SIGNAL(textChanged ( const QString & )));
    myDialog->leInterval->setText("123");
    myDialog->leInterval->setText("12234");
    myDialog->leInterval->setText("1000");
    QCOMPARE(3,s.count());
}


void TimerDialogTest::userEnterText() {
    myDialog->leInterval->setText("");
    QTest::keyPress(myDialog->leInterval,Qt::Key_1);
    QTest::keyPress(myDialog->leInterval,Qt::Key_2);
    QTest::keyPress(myDialog->leInterval,Qt::Key_3);
    QTest::keyPress(myDialog->leInterval,Qt::Key_1);
    QTest::keyPress(myDialog->leInterval,Qt::Key_0);

    QCOMPARE(myDialog->leInterval->text().toInt(), 12310);
}

void TimerDialogTest::userClickSetAndStop(){
    myDialog->leInterval->setText("123");
  
    myDialog->cbChooseTimer->setCurrentIndex(0);
    QTest::mouseClick(myDialog->btnSet,Qt::LeftButton);

    QCOMPARE(myDialog->isTimerOn[0], true);
    QCOMPARE(myDialog->isTimerOn[1], false);

    myDialog->cbChooseTimer->setCurrentIndex(1);
    QTest::mouseClick(myDialog->btnSet,Qt::LeftButton);
    QCOMPARE(myDialog->isTimerOn[0], true);
    QCOMPARE(myDialog->isTimerOn[1], true);

    QTest::mouseClick(myDialog->btnStop,Qt::LeftButton);
    QCOMPARE(myDialog->isTimerOn[0], true);
    QCOMPARE(myDialog->isTimerOn[1], false);

    myDialog->cbChooseTimer->setCurrentIndex(0);
    QTest::mouseClick(myDialog->btnStop,Qt::LeftButton);
    QCOMPARE(myDialog->isTimerOn[0], false);
    QCOMPARE(myDialog->isTimerOn[1], false);


}

void TimerDialogTest::timersWorkTest() {
    myDialog->leInterval->setText("1");

    QVERIFY(myDialog->countTimer[0] == 0);
    QVERIFY(myDialog->countTimer[1] == 0);


    myDialog->setTimer();
    myDialog->cbChooseTimer->setCurrentIndex(1);
    myDialog->setTimer();

    QTest::qWait(1000);
    myDialog->stopTimer();
    myDialog->cbChooseTimer->setCurrentIndex(0);
    myDialog->stopTimer();

    QVERIFY(myDialog->countTimer[0] != 0);
    QVERIFY(myDialog->countTimer[1] != 0);
}
