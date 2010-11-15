#ifndef TEST_TIMER_H
#define TEST_TIMER_H

#include <QObject>

#include "../src/TimerDialog.h"

class TestTimer: public QObject{
	Q_OBJECT;
public:
	TestTimer();

private:
	TimerDialog* timerDialog;
	int testTimerPeriod;

private slots:
        void testTimerPeriod1();
        void testTimerPeriod2();
        void testTimerComboBox();
        void testStopTimers();
};

#endif // TEST_TIMER_H
