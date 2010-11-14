#ifndef _TEST_TIMERS_H_
#define _TEST_TIMERS_H_

#include "../src/TimerDialog.h"

class TestTimers : public QObject {
	Q_OBJECT
public:
	TestTimers(QObject *parent = 0);

private slots:
	void test1();
	void test2();
	void test3();

private:
	TimerDialog *myTimerDialog;
};

#endif // _TEST_TIMERS_H_
