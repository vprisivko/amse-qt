#ifndef _TIMER_TEST_H_
#define _TIMER_TEST_H_

#include <Qt>
#include "../src/dialog.h"

class TimerTest : public QObject {
    Q_OBJECT;

    public:
        TimerTest();
        ~TimerTest();

    private slots:
        void testSignals(); //change timer test
        void testSemantic(); //set period test
        void testSetValueToTimer(); //set value to timer test

    private:
      Dialog *myDialog;
};

#endif
