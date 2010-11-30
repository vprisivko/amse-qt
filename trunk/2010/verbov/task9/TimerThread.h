#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

#include <QThread>
#include <QMutex>

class TimerThread : public QThread {
    Q_OBJECT
public:
    TimerThread(QObject *parent = 0);
    void set(int interval, int *counter, QMutex *locker);

protected:
    void run();

private:
    int myInterval;
    int *myCounter;
    QMutex *myLocker;
};

#endif // TIMERTHREAD_H
