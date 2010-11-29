#include "timer.h"

Timer::Timer(int interval, int *counter, QMutex *lock) {
    this->interval = interval;
    this->counter = counter;
    this->lock = lock;
}

void Timer::run() {
    while(true) {
        usleep(interval * 1000);
        lock->lock();
        (*counter)++;
        lock->unlock();
    }
}
