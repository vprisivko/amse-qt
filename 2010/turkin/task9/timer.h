#ifndef TIMER_H
#define TIMER_H

#include <QThread>
#include <QMutex>

class Timer : public QThread {
    Q_OBJECT;
    public:
        Timer(QObject *parent = 0);
        void setParameters(int* counter, int interval, QMutex* mutex);


    public slots:
        void stop(Timer* stoppingTimer);

    protected:
         virtual void run();

    private:
        bool isAlive();
    private:
        int* myCounter;
        QMutex* myMutex;
        int myInterval;

    private:
        bool myIsAlive;


};

#endif // TIMER_H
