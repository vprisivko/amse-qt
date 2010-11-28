/*
 * Timer.h
 *
 *  Created on: 28.11.2010
 *      Author: Korgov Kirill
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <QThread>
#include <QMutex>

class Timer: public QThread
{
    Q_OBJECT;
private:
    int myInterval;
    QMutex* myMutex;
    int myCounter;

public:
    Timer(QObject *parent);
    virtual ~Timer();
    int getCounter() const { return myCounter; }
    QMutex* getMutex() const { return myMutex; }
    void run();
    void setAll(int interval, int startvalue);
};

#endif /* TIMER_H_ */
