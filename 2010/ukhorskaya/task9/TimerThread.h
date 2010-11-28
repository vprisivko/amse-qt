#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

#include <QThread>
#include <QMutex>

class TimerThread: public QThread {
    Q_OBJECT;

public:
    int m_period;
    int *m_time;

    QMutex mutex;
    TimerThread(int period, int *time);

public:
    void run();
};

#endif // TIMERTHREAD_H
