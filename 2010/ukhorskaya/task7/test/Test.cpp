#include <QTest>
#include <QSignalSpy>

#include "Test.h"

Test::Test():QObject() {
    m_dialog = new MyDialog();
}
void Test::setTimer() {
    QTest::keyPress(m_dialog -> intervalLineEdit, Qt::Key_5);
    QTest::keyPress(m_dialog -> intervalLineEdit, Qt::Key_0);
    QTest::mouseClick(m_dialog -> setButton, Qt::RightButton);

    int period = m_dialog -> intervalLineEdit->text().toInt();
    m_dialog -> intervalLineEdit->setText("");

    QCOMPARE(50, period);
}

void Test::testChangeTimer() {
    QSignalSpy signalSpy(m_dialog -> changeTimerComboBox, SIGNAL(currentIndexChanged(int)));
    m_dialog -> changeTimerComboBox -> setCurrentIndex(1);
    m_dialog -> changeTimerComboBox -> setCurrentIndex(0);

    QCOMPARE(2, signalSpy.count());
}
void Test::testSetPeriod() {
    QTest::keyPress(m_dialog -> intervalLineEdit, Qt::Key_5);
    QTest::keyPress(m_dialog -> intervalLineEdit, Qt::Key_0);
    QTest::mouseClick(m_dialog -> setButton, Qt::LeftButton);
    int period = m_dialog -> intervalLineEdit -> text().toInt();

    QCOMPARE(m_dialog -> firstTimerPeriod, period);
}


