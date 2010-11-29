#ifndef TIMER_H
#define TIMER_H

#include <QThread>
#include <QMutex>

class Timer : public QThread{
    Q_OBJECT;

    public:
        Timer( int* countValue, int delayValue, QMutex* mutex );
        void run();

    private:
        int* myCountValue;
        int myDelayValue;
        QMutex* myMutex;
};

#endif // TIMER_H
