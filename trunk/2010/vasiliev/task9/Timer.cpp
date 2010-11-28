#include "Timer.h"

Timer::Timer(int delay, int *currCount, QMutex *mutex): QThread(),
	myDelay(delay),
	myCount(currCount),
	myMutex (mutex) {
}

void Timer::run() {
	while(1) {
		usleep(myDelay * 1000);
		myMutex->lock();
		++(*myCount);
		myMutex->unlock();
	}
}
