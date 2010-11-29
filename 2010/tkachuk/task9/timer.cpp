#include "timer.h"

Timer::Timer(QObject *p) : QThread(p) {
	stopped = false;
}

void Timer::setParams(int *counter, int timeInterval, QMutex *mutex) {
	myCounter = counter;
	myInterval = timeInterval;
	myMutex = mutex;
}

void Timer::run() {
	int i = 0;
	while (1) {
		i++;
		if (stopped) {
			break;
		}
		if (i == myInterval) {
			myMutex->lock();
			(*myCounter)++;
			myMutex->unlock();
			i = 0;
		}
		msleep(1);
	}
	stopped = false;
}

void Timer::stop() {
	stopped = true;
}
