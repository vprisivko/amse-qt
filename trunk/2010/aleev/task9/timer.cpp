#include "timer.h"

Timer::Timer(QObject *parent) : QThread(parent) {
    myIsAlive = false;
}

void Timer::run() {
    myIsAlive = true;

    while (myIsAlive) {
        msleep(myInterval);
        myMutex->lock();
        ++(*myCounter);
        myMutex->unlock();
    }
}

void Timer::stop(Timer* timer) {
    if (timer == this) {
        myIsAlive = false;
    }
}

void Timer::setParams(int* counter, int interval, QMutex* mutex) {
    myCounter = counter;
    myInterval = interval;
    myMutex = mutex;
}
