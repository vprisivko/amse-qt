#ifndef TIMETHREAD_H
#define TIMETHREAD_H

#include <QMutex>
#include <QThread>

class TimeThread:public QThread{
  Q_OBJECT;
  private:
  int myperiod;
  int mycounter;
  QMutex* mymutex;
  public:
  TimeThread(QMutex* mutex,int period=1, QObject* parent =0);

  void run();
  void setPeriod(int period);
  int getTime();
};

#endif
