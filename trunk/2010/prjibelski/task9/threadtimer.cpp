#include <iostream>

#include "threadtimer.h"

ThreadTimer::ThreadTimer(unsigned int * timerCurrentTime):
        currentTime( timerCurrentTime )
{
}

void ThreadTimer::run() {
    if ( period == 0 ) {
        return;
    }

    while( true ) {
        this->msleep( period );

        timerMutex.lock();
        (*currentTime) += period;
        timerMutex.unlock();
    }
}
