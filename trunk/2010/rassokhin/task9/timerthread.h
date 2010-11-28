#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

#include <QThread>
#include "myatomicint.h"

class TimerThread : public QThread {
public:
    TimerThread(MyAtomicInt * time, MyAtomicInt * counter);

protected:
    void run();

private:
    MyAtomicInt * myTime;
    MyAtomicInt * myCounter;
};

#endif // TIMERTHREAD_H
