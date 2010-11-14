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

        void testPeriod();
        void setValueToTimer();
        void testChangeTimer();


    private:
      Dialog* myDialog;

    

};

#endif

