#include "TimerThread.h"

TimerThread::TimerThread(int period,  int* time){
    m_period = period;
    m_time = time;
}
void TimerThread::run(){
     while (true) {
         msleep(m_period);
         mutex.lock();
         (*m_time)++;
         mutex.unlock();
     }
}
