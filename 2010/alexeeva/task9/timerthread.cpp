#include "timerthread.h"


void TimerThread::set(int interval , int * ticks, QMutex * lock) {
    m_ticks = ticks;
    m_interval = interval;
    m_lock = lock;
}

void TimerThread::run() {
    while (true) {
        usleep(m_interval * 1000);

        m_lock->lock();
        (*m_ticks)++;
        m_lock->unlock();
    }
}

