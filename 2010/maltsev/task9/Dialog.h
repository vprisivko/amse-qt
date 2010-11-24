#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QEvent>
#include <QComboBox>
#include <QMutex>
#include "TimerThread.h"

class Dialog: public QDialog {
Q_OBJECT;

public:
  Dialog(QWidget *w = 0);

private:
  TimerThread t1, t2;
  int activetimer, c1, c2;
  QMutex lock1, lock2;
  QLabel *lb1, *lb2;
  QLineEdit *ed;
  QComboBox* cb;

protected:
  virtual void timerEvent(QTimerEvent*);

public slots:
    void cboxchanged(int);
    void btnstop();
    void btnset();

};

#endif
