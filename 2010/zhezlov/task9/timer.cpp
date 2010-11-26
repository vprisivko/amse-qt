#include "timer.h"

Timer::Timer(QObject *parent) : QThread(parent){
}

void Timer::set(int interval, int *counter, QMutex *mutex){
    this->interval = interval;
    this->counter = counter;
    this->mutex = mutex;
    moar = true;
    start();
}

void Timer::run(){
    while( moar ){
        msleep(interval); //usleep(interval); // lags.
        mutex->lock();
        (*counter)++;
        mutex->unlock();
        emit tick();
    }
}

void Timer::stop(Timer *who){
    if ( who == this ) moar = false;
}
