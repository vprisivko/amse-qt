#ifndef _TIMER_H_
#define _TIMER_H_

#include <QThread>
#include <QMutex>

class Timer : public QThread {
    Q_OBJECT;

    public:
        Timer(QObject *parent = 0);
        void setParams(int *counter, int interval, QMutex *mutex);

    public slots:
        void stop(Timer *stoppingTimer);

    protected:
         virtual void run();

    private:
        bool myIsAlive;
        int *myCounter;
        QMutex *myMutex;
        int myInterval;
};

#endif
