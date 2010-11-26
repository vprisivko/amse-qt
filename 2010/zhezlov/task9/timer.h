#ifndef TIMER_H
#define TIMER_H

#include <QThread>
#include <QMutex>

class Timer : public QThread
{
    Q_OBJECT
public:
    explicit Timer(QObject *parent = 0);
    void set(int interval, int* counter, QMutex* mutex);

protected:
    void run();

private:
    int interval;
    int* counter;
    QMutex* mutex; //K.O.
    bool moar;

signals:
    void tick();

public slots:
    void stop(Timer* who);

};

#endif // TIMER_H
