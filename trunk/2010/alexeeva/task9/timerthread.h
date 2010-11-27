#ifndef TIMERTHREADS_H
#define TIMERTHREADS_H

#include <QtGui/QWidget>
#include <QMutex>
#include <QThread>

class TimerThread : public QThread
{
    Q_OBJECT

public:
    TimerThread(QWidget * parent = 0) : QThread(parent) {} ;
    void set(int, int*, QMutex*);
    void run();

private:
    int m_interval;
    int * m_ticks;
    QMutex * m_lock;
};

#endif // TIMERTHREADS_H
