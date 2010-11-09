#include<QTest>
#include <QtTest>
#include<QSignalSpy>
#include"Test1.h"

Test1::Test1():QObject(){
    m_dial = new MyDialog();


}
void Test1::setValueToTimer() {

    QTest::keyPress(m_dial->setLineEdit,Qt::Key_1);
    QTest::keyPress(m_dial->setLineEdit,Qt::Key_0);
    QTest::mouseClick(m_dial->setButton,Qt::LeftButton);
    int period = m_dial->setLineEdit->text().toInt();
    testTimerPeriod = 10;
    QCOMPARE(testTimerPeriod,period);
}

void Test1::testChangeTimer(){
QSignalSpy s(m_dial->timerCombo,SIGNAL(currentIndexChanged(int)));
m_dial->timerCombo->setCurrentIndex(1);
m_dial->timerCombo->setCurrentIndex(0);
m_dial->timerCombo->setCurrentIndex(1);
QCOMPARE(3,s.count());
}
void Test1::testSetPeriod(){
    QTest::keyPress(m_dial->setLineEdit,Qt::Key_1);
    QTest::keyPress(m_dial->setLineEdit,Qt::Key_0);
    QTest::mouseClick(m_dial->setButton,Qt::LeftButton);
    int period = m_dial->setLineEdit->text().toInt();
    QCOMPARE(m_dial->period1,period);

}


