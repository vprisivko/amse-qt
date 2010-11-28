#ifndef _TIMER_H_
#define _TIMER_H_

#include <QThread>
#include <QMutex>

class Timer: public QThread {

Q_OBJECT;

public:
	Timer(int delay, int *currCount, QMutex *mutex);
	void run();

private:
	const int myDelay;

	int *myCount;
	QMutex *myMutex;
};

#endif // _TIMER_H_
