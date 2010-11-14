#ifndef _TEST_H_
#define _TEST_H_

#include<QTest>
#include<Qt>
#include<QSignalSpy>
#include"../src/MyDialog.h"

class MyTest : public QObject{
    Q_OBJECT;

    public:
        MyTest();
        ~MyTest();

    private slots:
        void testSetTimerValue();
        void testSetButton();
        void testChangeTimers();
        void testTimer();

    public:
        MyDialog* myDialog;
};

#endif
