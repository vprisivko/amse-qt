#include "IntervalThread.h"

IntervalThread::IntervalThread(QObject *parent): QThread(parent){

    isNeeded = false;

}

void IntervalThread::setParams(int interval, int& counter, QMutex *mutex){

    this->interval = interval;
    this->counter = &counter;
    this->mutex = mutex;

}

void IntervalThread::run(){

    isNeeded = true;

    while(isNeeded){

        mutex->lock();
        (*counter)++;
        mutex->unlock();
        msleep(interval);

    }
}

void IntervalThread::stop(){

        isNeeded = false;
}

bool IntervalThread::isRunning(){

        return isNeeded;
}
