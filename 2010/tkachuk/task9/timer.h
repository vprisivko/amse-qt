#ifndef TIMER_H
#define TIMER_H

#include <QThread>
#include <QMutex>

class Timer : public QThread {
	Q_OBJECT

public:
	Timer(QObject *p = NULL);
	void setParams(int *counter, int timeInterval, QMutex *mutex);
	void stop();

protected:
	void run();

private:
	int *myCounter;
	int myInterval;
	QMutex *myMutex;
	volatile bool stopped;
};

#endif // TIMER_H
