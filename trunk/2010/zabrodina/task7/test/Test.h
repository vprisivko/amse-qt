#ifndef TEST_H
#define TEST_H

#include <QObject>
#include"../src/MyDialog.h"

class Test: public QObject{
    Q_OBJECT;

public:
    MyDialog *m_dialog;

    Test();

private slots:
    void setTimer();
    void testChangeTimer();
    void testSetPeriod();
};

#endif // TEST_H
