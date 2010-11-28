// =====================================================================================
// 
//       Filename:  timer.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  28.11.2010 13:13:56
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#include "timer.h"

Timer::Timer(int *variable, QMutex *mutex, int interval, QObject *parent) : 
    QThread(parent), myVariable(variable), myMutex(mutex), myInterval(interval){
}

void Timer::run() {
    while(1) {
        msleep(myInterval);
        myMutex->lock();
        (*myVariable)++;
        myMutex->unlock();
    }
}
