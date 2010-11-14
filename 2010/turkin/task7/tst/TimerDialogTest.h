#ifndef TIMER_TEST_H
#define TIMER_TEST_H

#include <Qt>

#include "../src/dialog.h"

class TimerDialogTest:public QObject {
    Q_OBJECT;

    public:
        TimerDialogTest();
        ~TimerDialogTest();

    private slots:

        //user enter digits, then click set and stop on different timers
        void userClickSetAndStop();
        // user enter text checking
        void userEnterText();
        //turning timers on and off
        void testTimerOnOff();
        //signal test
        void testSignalIntervalChange();
        //test timers are really count
        void timersWorkTest();


    private:
      Dialog* myDialog;

    

};

#endif

