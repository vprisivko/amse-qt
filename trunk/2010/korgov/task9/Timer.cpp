/*
 * Timer.cpp
 *
 *  Created on: 28.11.2010
 *      Author: Korgov Kirill
 */

#include "Timer.h"

Timer::Timer(QObject *parent)
    : QThread(parent),
      myCounter(0)
{
    myMutex = new QMutex();
}

Timer::~Timer()
{
}

void Timer::run()
{
    while(true){
        this->usleep(myInterval*1000);
        myMutex->lock();
        myCounter++;
        myMutex->unlock();
    }
}

void Timer::setAll(int interval, int startValue)
{
    myInterval = interval;
    myCounter = startValue;
}
