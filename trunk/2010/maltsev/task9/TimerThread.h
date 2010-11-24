#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

#include <QThread>
#include <QMutex>

class TimerThread: public QThread {
Q_OBJECT;

public:
    TimerThread(QWidget *w = 0);
    void set(int, int*, QMutex*);

protected:
    void run();

private:
    int my_interval, *my_counter;
    QMutex* my_lock;

};

#endif
