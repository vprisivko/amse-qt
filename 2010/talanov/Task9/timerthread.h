#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

#include <QtCore/QThread>
#include <QtCore/QMutex>

class TimerThread : public QThread
{
    Q_OBJECT
public:
    explicit TimerThread(int& counter, QMutex& mutex, QObject *parent = 0);

signals:

private:

    void run();

public:

    void setInterval(int intervalInMs);
    void setIsRunning(bool isRunning);

private:

    void increaseCount();

private:

    bool myIsRunning;
    int& myCounter;
    QMutex& myMutex;
    int myIntervalInMs;

};

#endif // TIMERTHREAD_H
