#ifndef MY_DIALOG_H
#define MY_DIALOG_H

#include <QtGui/QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QLCDNumber>
#include <QTimer>
#include <QEvent>

class MyDialog : public QDialog
{
    Q_OBJECT;

public:
  MyDialog(QWidget *parent = 0, Qt::WFlags flags = 0);

  void timerEvent(QTimerEvent *e);

public slots:
  void setInterval();
  void stopTimer();
  void changeCurrentTimer();

private:
  
  int timer_id;
  int timer_e;
  int currentTimerNumber;
  int currentTime1;
  int currentTime2;
  int timer1Interval;
  int timer2Interval;

  QLineEdit *intervalLineEdit;
  QComboBox *timersComboBox;
  QLCDNumber *timer1LCD;
  QLCDNumber *timer2LCD;
};

#endif // MY_DIALOG_H
