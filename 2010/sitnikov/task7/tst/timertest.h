#ifndef _TIMERTEST_H_
#define _TIMERTEST_H_

#include "dialogwrapper.h"


class TimerTest : public QObject
{
	Q_OBJECT;

public:
	TimerTest(QObject *parent = 0);

private:
	TimerTest(const TimerTest&);
	TimerTest& operator= (const TimerTest&);

private slots:
	void initTestCase();
	void cleanupTestCase();
	void firstTimerTestCase();
	void secondTimerTestCase();
	void bothTimersTestCase();

private:
	DialogWrapper *dialog_;
};

#endif
