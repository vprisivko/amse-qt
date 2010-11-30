#include "TimerThread.h"

TimerThread::TimerThread(QObject *parent) : QThread(parent) {
}

void TimerThread::set(int interval, int *counter, QMutex *locker) {
    myInterval = interval;
    myCounter = counter;
    myLocker = locker;
}

void TimerThread::run() {
    while (true) {
        usleep(myInterval * 1000);
        myLocker->lock();
        (*myCounter)++;
        myLocker->unlock();
    }
}
