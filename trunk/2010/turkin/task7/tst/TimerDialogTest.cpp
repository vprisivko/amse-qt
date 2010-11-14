#include <QTest>
#include <QSignalSpy>

#include "TimerDialogTest.h"

TimerDialogTest::TimerDialogTest() {
    myDialog = new Dialog();
}

TimerDialogTest::~TimerDialogTest() {
     delete myDialog;
}


void TimerDialogTest::setValueToTimer() {
    myDialog->leInterval->setText("");
    QTest::keyPress(myDialog->leInterval,Qt::Key_1);
    QTest::keyPress(myDialog->leInterval,Qt::Key_0);
    QTest::mouseClick(myDialog->btnSet,Qt::LeftButton);
    int period = myDialog->leInterval->text().toInt();
    QCOMPARE(10,period);
}

void TimerDialogTest::testChangeTimer(){
    QSignalSpy s(myDialog->cbChooseTimer,SIGNAL(currentIndexChanged(int)));
    myDialog->cbChooseTimer->setCurrentIndex(0);
    myDialog->cbChooseTimer->setCurrentIndex(1);
    myDialog->cbChooseTimer->setCurrentIndex(0);
    myDialog->cbChooseTimer->setCurrentIndex(1);
    QCOMPARE(3,s.count());
}
void TimerDialogTest::testPeriod(){
    myDialog->leInterval->setText("");
    QTest::keyPress(myDialog->leInterval,Qt::Key_1);
    QTest::keyPress(myDialog->leInterval,Qt::Key_0);
    QTest::mouseClick(myDialog->btnSet,Qt::LeftButton);
    int period = myDialog->leInterval->text().toInt();
    QCOMPARE( 10, myDialog->leInterval->text().toInt() );

}
