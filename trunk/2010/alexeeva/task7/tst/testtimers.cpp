#include "testtimers.h"

TestTimers::TestTimers()
    : QObject()
{
	m_dialog = new Dialog();
}

void TestTimers::testFirstTimer() {
    m_dialog->comboChooseTimer->setCurrentIndex(0);
    m_dialog->editInterval->setText("100");
    int timeFirstTimer = m_dialog->labValue1->text().toInt();

    /* Set signal spy */
    QSignalSpy signalsEmitted(m_dialog, SIGNAL(isSet()));

    /* Emulate mouse click */
    QTest::mouseClick(m_dialog->buttSet, Qt::LeftButton);

    /* compare if it was only one signal emitted */
    QCOMPARE(1, signalsEmitted.count());

    /* wait and compare if it was 'time_of_waiting/interval' ticks */
    QTest::qWait(555);
    QCOMPARE(timeFirstTimer + 5, m_dialog->labValue1->text().toInt());
}

void TestTimers::testSecondTimer() {
    m_dialog->comboChooseTimer->setCurrentIndex(1);
    m_dialog->editInterval->setText("100");
    int timeSecondTimer = m_dialog->labValue2->text().toInt();

    QSignalSpy signalsEmitted(m_dialog, SIGNAL(isSet()));

    QTest::mouseClick(m_dialog->buttSet, Qt::LeftButton);
    QCOMPARE(1, signalsEmitted.count());

    QTest::qWait(555);
    QCOMPARE(timeSecondTimer + 5, m_dialog->labValue2->text().toInt());
}
