#include "MyThread.h"

MyThread::MyThread(QWidget* parent) : QThread(parent){}

void MyThread::set(int interval, int* counter, QMutex* mutex){
  myInterval = interval;
  myCounter = counter;
  myMutex = mutex;
}

void MyThread::run(){
  while (true){
    usleep(myInterval*1000);
    myMutex->lock();
    (*myCounter)++;
    myMutex->unlock();
  }
}
