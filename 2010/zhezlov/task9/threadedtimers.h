#ifndef THREADEDTIMERS_H
#define THREADEDTIMERS_H

#include <QWidget>
#include <QMutex>
#include "timer.h"


namespace Ui {
    class ThreadedTimers;
}

class ThreadedTimers : public QWidget
{
    Q_OBJECT

public:
    explicit ThreadedTimers(QWidget *parent = 0);
    ~ThreadedTimers();

private:
    Ui::ThreadedTimers *ui;
    Timer* timers;
    QMutex* mutexes;
    int* counters;

public slots:
    void stop();
    void set();
    void tock();

signals:
    void stopTimer(Timer*);

};

#endif // THREADEDTIMERS_H
