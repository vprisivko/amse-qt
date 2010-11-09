#ifndef TEST1_H
#define TEST1_H
#include<QObject>
#include"../src/MyDialog.h"
class Test1 : public QObject{
    Q_OBJECT;
public:
    MyDialog *m_dial;
    int testTimerPeriod;
    Test1();
private slots:
    void setValueToTimer();//Gui test
    void testChangeTimer();//Signal's test
    void testSetPeriod();//test setter to class MyDialog. semantic's test
};

#endif // TEST1_H
