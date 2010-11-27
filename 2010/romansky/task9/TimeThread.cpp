#include "TimeThread.h"

TimeThread::TimeThread(QMutex* mutex,int period , QObject* parent):QThread(parent){
  myperiod = period;
  mycounter = 0;
  mymutex = mutex;
}

void TimeThread::run(){
  while (true){
    msleep(myperiod);
    mymutex->lock();
    mycounter++;
    mymutex->unlock();
  }
}

void TimeThread::setPeriod(int period){
  if (period > 0){
    myperiod = period;
  }
}

int TimeThread::getTime(){
  return mycounter;
}
