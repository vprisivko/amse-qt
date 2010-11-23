#ifndef MYTEST_H
#define MYTEST_H

#include <QObject>
#include "../src/TimerDialog.h"

class MyTest : public QObject{
    Q_OBJECT;

private:

    TimerDialog * dialogToTest;

private slots:

    void initTestCase();

    void firstTimerCheck();
    void comboBoxTest();
    void secondTimerCheck();
    void stopButtonClickTest();
    void setButtonClickTest();

    void cleanupTestCase();
};

#endif // MYTEST_H
