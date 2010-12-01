#ifndef THREADCOUNTER_H
#define THREADCOUNTER_H

#include <QThread>
#include <QMutex>


class ThreadCounter : public QThread {
	Q_OBJECT;

	public:
		ThreadCounter(int step, int count);

	public:
		void setStep(int step);
		int getTime();

	private:
		void run();

	private:
		QMutex mutex;
		int step;
		int count;
};

#endif
