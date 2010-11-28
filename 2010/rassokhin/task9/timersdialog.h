#ifndef __TIMERS_DIALOG_H
#define __TIMERS_DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>

#include "timerthread.h"

namespace Ui {
    class TimersDialog;
};

class TimersDialog : public QDialog {
    Q_OBJECT;

public:
    TimersDialog(QWidget * parent = 0);
    ~TimersDialog();

protected slots:
    void counterChanged(int value);
    void setTimer();
    void stopTimer();

private:
    Ui::TimersDialog * ui;

    TimerThread *timer;
    MyAtomicInt counter;
    MyAtomicInt timerInterval;

};

#endif
