#ifndef THREADTIMER_H
#define THREADTIMER_H

#include <QThread>
#include <QMutex>

class ThreadTimer : public QThread
{
    Q_OBJECT;

private:
    unsigned int period;
    unsigned int * currentTime;

public:
    ThreadTimer(unsigned int * timerCurrentTime);
    void run();

    void setPeriod(int timePerod) {
        timerMutex.lock();
        period = timePerod;
        timerMutex.unlock();
    }

    QMutex timerMutex;

};

#endif // THREADTIMER_H
