#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H
#include <QThread>
#include <QMutex>
class TimerThread: public QThread{
    Q_OBJECT;
public:
    int period;
    int *currentTime;
    QMutex mutex;
    TimerThread(int _period, int *prevTime );
protected:
    void run();
};

#endif // TIMERTHREAD_H
