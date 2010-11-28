#ifndef INTERVALTHREAD_H
#define INTERVALTHREAD_H

#include <QThread>
#include <QMutex>

class IntervalThread : public QThread{
    Q_OBJECT;

public:
    IntervalThread(QObject *parent = 0);
    void setParams(int, int&, QMutex*);
    bool isRunning();
    void stop();

protected:
    virtual void run();

private:
    int interval;
    int* counter;
    QMutex *mutex;
    bool isNeeded;


};

#endif // INTERVALTHREAD_H
