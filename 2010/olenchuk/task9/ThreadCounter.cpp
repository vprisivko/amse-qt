#include "ThreadCounter.h"

#include <QMutexLocker>

ThreadCounter :: ThreadCounter(int step, int count) {
	this->step = step;
	this->count = count;
}
void ThreadCounter :: run() {
	forever {
		{
			QMutexLocker locker(&mutex);
			++count;
		}
		msleep(step);
	}
}
int ThreadCounter :: getTime() {
	QMutexLocker locker(&mutex);
	return count;
}
void ThreadCounter :: setStep(int step) {
	this->step = step;
}
