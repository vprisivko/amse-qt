#ifndef TIMERDIALOG_H
#define TIMERDIALOG_H

#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtCore/QString>
#include <QtCore/QMutex>

#include "timerthread.h"

class TimerDialog : public QDialog
{
  Q_OBJECT

public:

  TimerDialog(QWidget *parent = 0, Qt::WFlags flags = 0);
  ~TimerDialog();

private slots:

  void setActiveTimer(int timerIndex);
  void refreshLabels();
  void resetActiveTimer();
  void stopActiveTimer();
  void setCurrentInterval(const QString&);

protected:

  void timerEvent(QTimerEvent *);


private:

  QLabel *myCountLabel1, *myCountLabel2;
  TimerThread myTimer1, myTimer2;
  int myCounter1, myCounter2;
  QMutex myCounterMutex1, myCounterMutex2;
  int myTimerId1, myTimerId2;
  int myActiveTimerIndex;
  int myCurrentInterval;

};

#endif // TIMERDIALOG_H
