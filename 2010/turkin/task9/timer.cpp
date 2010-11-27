#include "timer.h"

Timer::Timer(QObject *parent) : QThread(parent) {
    myIsAlive = false;
}

void Timer::setParameters(int* counter, int interval, QMutex* mutex) {  
    myCounter = counter;
    myInterval = interval;
    myMutex = mutex;
}


void Timer::run() {
    myIsAlive = true;

    while ( myIsAlive ) {
        msleep(myInterval);
        myMutex->lock();
        (*myCounter)++;
        myMutex->unlock();
    }

}


void Timer::stop(Timer* stoppingTimer) {
    if (stoppingTimer == this) {
        myIsAlive = false;
    }
}
