/*
 * SignalsTest.h
 *
 *  Created on: 14.11.2010
 *      Author: Korgov Kirill
 */

#ifndef SIGNALSTEST_H_
#define SIGNALSTEST_H_

#include <QTest>
#include <QTest>
#include <QSignalSpy>

#include "../src/TimerDialog.h"

class TestTimerDialog: public QObject
{
    Q_OBJECT;
private:
    TimerDialog *myTimerDialog;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testTimer1();
    void testTimer2();
};

#endif /* SIGNALSTEST_H_ */
