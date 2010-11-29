#ifndef TIMER_H
#define TIMER_H

#include <QThread>
#include <QMutex>

class Timer : public QThread {
private:
    int interval;
    int *counter;
    QMutex *lock;

public:
    Timer(int interval, int *counter, QMutex *lock);
    int getCounter();
    void run();
};

#endif // TIMER_H
