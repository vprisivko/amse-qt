#include <QTest>
#include <QSignalSpy>

#include "TimerTest.h"

TimerTest::TimerTest() {
    myDialog = new Dialog();
}

TimerTest::~TimerTest() {
     delete myDialog;
}

void TimerTest::testSignals(){
    QSignalSpy s(myDialog->timersComboBox,SIGNAL(currentIndexChanged(int)));
    myDialog->timersComboBox->setCurrentIndex(0);
    myDialog->timersComboBox->setCurrentIndex(1);
    myDialog->timersComboBox->setCurrentIndex(0);
    myDialog->timersComboBox->setCurrentIndex(1);
    QCOMPARE(3,s.count());
}

void TimerTest::testSetValueToTimer() {
    myDialog->setIntervalLineEdit->setText("");
    QTest::keyPress(myDialog->setIntervalLineEdit,Qt::Key_1);
    QTest::keyPress(myDialog->setIntervalLineEdit,Qt::Key_0);
    QTest::mouseClick(myDialog->setButton,Qt::LeftButton);
    int period = myDialog->setIntervalLineEdit->text().toInt();
    QCOMPARE(10,period);
}

void TimerTest::testSemantic(){
    myDialog->setIntervalLineEdit->setText("");
    QTest::keyPress(myDialog->setIntervalLineEdit,Qt::Key_1);
    QTest::keyPress(myDialog->setIntervalLineEdit,Qt::Key_0);
    QTest::mouseClick(myDialog->setButton,Qt::LeftButton);
    int period = myDialog->setIntervalLineEdit->text().toInt();
    QCOMPARE(10, myDialog->setIntervalLineEdit->text().toInt());
}
