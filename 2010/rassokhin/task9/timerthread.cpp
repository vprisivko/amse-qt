#include "timerthread.h"

TimerThread::TimerThread(MyAtomicInt *time, MyAtomicInt *counter)
        :myTime(time), myCounter(counter) {
}

void TimerThread::run() {
    while (1) {
        if (myTime->get() < 0) return;
        msleep(myTime->get());
        myCounter->inc();
    }
}
