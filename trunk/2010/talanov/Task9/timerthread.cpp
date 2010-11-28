#include "timerthread.h"

#include <QtTest>

TimerThread::TimerThread(int& counter, QMutex& mutex, QObject *parent) :
    QThread(parent), myCounter(counter), myMutex(mutex)
{
    myIsRunning = false;
    myIntervalInMs = 0;
}

void TimerThread::run() {
    while (true) {
        if (myIsRunning) {
            QTest::qSleep(myIntervalInMs);
            increaseCount();
        }
    }
}

void TimerThread::increaseCount() {
    QMutexLocker locker(&myMutex);
    ++myCounter;
}

void TimerThread::setInterval(int intervalInMs) {
    myIntervalInMs = intervalInMs;
}

void TimerThread::setIsRunning(bool isRunning) {
    myIsRunning = isRunning;
}
