#include "TimerThread.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>

TimerThread::TimerThread(QWidget *parent): QThread(parent) {
    //
}

void TimerThread::set(int interval , int* counter, QMutex* lock) {
    my_counter = counter;
    my_interval = interval;
    my_lock = lock;
}


void TimerThread::run() {
    while (true) {
        usleep(my_interval * 1000);
        my_lock->lock();
        (*my_counter)++;
        my_lock->unlock();
    }
}

