#include "TimerThread.h"
TimerThread :: TimerThread(int _period,  int *prevTime){
    period = _period;
    currentTime = prevTime;
}
void TimerThread::run(){
     while(true){
         usleep(period*1000);
         mutex.lock();
         (*currentTime) += period;
         mutex.unlock();
     }

}
