#ifndef TIMERDIALOGTEST_H
#define TIMERDIALOGTEST_H

#include "../Task2/timerdialog.h"

#include <QObject>

class TimerDialogTest : public QObject
{
  Q_OBJECT

public:
    TimerDialogTest(QObject *parent = 0);
    ~TimerDialogTest();

private slots:

  void testLogic();
  void testInterfaceAndSignals();
  void testToFail();

private:

  TimerDialog* myTimerDialog;
    
};

#endif // TIMERDIALOGTEST_H
