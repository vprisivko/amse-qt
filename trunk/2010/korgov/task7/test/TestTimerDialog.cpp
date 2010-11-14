/*
 * SignalsTest.cpp
 *
 *  Created on: 14.11.2010
 *      Author: Korgov Kirill
 */

#include "TestTimerDialog.h"

void TestTimerDialog::initTestCase()
{
    myTimerDialog = new TimerDialog();
}

void TestTimerDialog::cleanupTestCase()
{
    delete myTimerDialog;
}

void TestTimerDialog::testTimer1()
{
    myTimerDialog->myComboBox->setCurrentIndex(1);

    QSignalSpy comboBoxSignalSpy(myTimerDialog->myComboBox, SIGNAL(currentIndexChanged(int)));
    myTimerDialog->myComboBox->setCurrentIndex(0);
    QCOMPARE(comboBoxSignalSpy.count(), 1);

    myTimerDialog->myIntervalInput->setText("100");
    int valueBeforeStart = myTimerDialog->myTimer1ValueLabel->text().toInt();
    QTest::mouseClick(myTimerDialog->mySetButton, Qt::LeftButton);
    QTest::qWait(130);
    QCOMPARE(valueBeforeStart + 1, myTimerDialog->myTimer1ValueLabel->text().toInt());

    QTest::qWait(230);
    QCOMPARE(valueBeforeStart + 3, myTimerDialog->myTimer1ValueLabel->text().toInt());

    myTimerDialog->myComboBox->setCurrentIndex(1);
    myTimerDialog->myComboBox->setCurrentIndex(0);
    QCOMPARE(comboBoxSignalSpy.count(), 3);

    int valueBeforeStop = myTimerDialog->myTimer1ValueLabel->text().toInt();
    QTest::mouseClick(myTimerDialog->myStopButton, Qt::LeftButton);
    QTest::qWait(230);
    QCOMPARE(valueBeforeStop, myTimerDialog->myTimer1ValueLabel->text().toInt());

}

void TestTimerDialog::testTimer2()
{
    myTimerDialog->myComboBox->setCurrentIndex(0);
    QSignalSpy comboBoxSignalSpy(myTimerDialog->myComboBox, SIGNAL(currentIndexChanged(int)));
    myTimerDialog->myComboBox->setCurrentIndex(1);
    QCOMPARE(comboBoxSignalSpy.count(), 1);

    myTimerDialog->myIntervalInput->setText("");
    QTest::keyClicks(myTimerDialog->myIntervalInput, "100");
    QCOMPARE(myTimerDialog->myIntervalInput->text(), QString("100"));
    int valueBeforeStart = myTimerDialog->myTimer2ValueLabel->text().toInt();
    QTest::mouseClick(myTimerDialog->mySetButton, Qt::LeftButton);
    QTest::qWait(130);
    QCOMPARE(valueBeforeStart + 1, myTimerDialog->myTimer2ValueLabel->text().toInt());
}
