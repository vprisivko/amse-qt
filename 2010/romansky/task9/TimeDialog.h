#ifndef TIMEDIALOG_H
#define TIMEDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTimerEvent>
#include <QMutex>
#include "TimeThread.h"

class TimeDialog:public QDialog{
  Q_OBJECT;
  private:
  QLabel* myfirsttimelabel;
  QLabel* mysecondtimelabel;
  QComboBox* mybox;
  QLineEdit* myset;

  TimeThread* myfirstthread;
  TimeThread* mysecondthread;

  QMutex* myfirstmutex;
  QMutex* mysecondmutex;
  QMutex* mymainmutex;

  public:
  TimeDialog(QWidget* parent=0);

  private:
  void timerEvent(QTimerEvent* e);

  public slots:
  void Set();
  void Stop();
};

#endif
