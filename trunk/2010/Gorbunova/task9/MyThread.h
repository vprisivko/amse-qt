#ifndef _MYTHREAD_
#define _MYTHREAD_
#include <QWidget>
#include <QMutex>
#include <QThread>

class MyThread : public QThread{
  Q_OBJECT

public:
  MyThread(QWidget * parent = 0);
  void set(int interval, int* counter, QMutex* mutex);
  void run();

private:
  int myInterval;
  int* myCounter;
  QMutex* myMutex;
    
};

#endif
