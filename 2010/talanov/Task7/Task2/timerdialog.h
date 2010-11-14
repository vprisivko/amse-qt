#ifndef TIMERDIALOG_H
#define TIMERDIALOG_H

#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtCore/QString>

class TimerDialog : public QDialog
{
  Q_OBJECT

public:

  TimerDialog(QWidget *parent = 0, Qt::WFlags flags = 0);
  ~TimerDialog();

private slots:

  void increaseCount(QLabel* countLabel);
  void setActiveTimer(int timerIndex);
  void resetActiveTimer();
  void stopActiveTimer();
  void setCurrentInterval(const QString&);

protected:

  void timerEvent(QTimerEvent *);


private:

  QLabel *myCountLabel1, *myCountLabel2;
  int myTimerId1, myTimerId2;
  int myActiveTimerIndex;
  int myCurrentInterval;

  friend class TimerDialogTest;
};

#endif // TIMERDIALOG_H
