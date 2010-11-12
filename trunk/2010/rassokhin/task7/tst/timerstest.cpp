#include "timerstest.h"
#include <Qt>
#include <QThread>

TimersTest::TimersTest(QObject *parent) :
        QObject(parent) {
}

void TimersTest::initTestCase() {
    m_dialog = new TimersDialog();
}

void TimersTest::firstTimerTest() {
    m_dialog->combo->setCurrentIndex(0);
    m_dialog->intervalEdit->setText("242");
    int count1 = m_dialog->timer1Counter;
    QTest::mouseClick(m_dialog->setButton, Qt::LeftButton);
    QTest::qWait(1500);
    QCOMPARE(m_dialog->timer1Interval, 242);
    QCOMPARE(count1 + 6, m_dialog->timer1Label->text().toInt());
    QTest::mouseClick(m_dialog->stopButton, Qt::LeftButton);
}

void TimersTest::secondTimerTest() {
    m_dialog->combo->setCurrentIndex(1);
    m_dialog->intervalEdit->setText("387");
    int count2 = m_dialog->timer2Counter;
    QTest::mouseClick(m_dialog->setButton, Qt::LeftButton);
    QTest::qWait(2800);
    QCOMPARE(m_dialog->timer2Interval, 387);
    QCOMPARE(count2 + 7, m_dialog->timer2Label->text().toInt());
    QTest::mouseClick(m_dialog->stopButton, Qt::LeftButton);
}

void TimersTest::cleanupTestCase() {
    delete m_dialog;
}
