#ifndef _TEST_H_
#define _TEST_H_

#include <Qt>
#include <QTest>
#include <QSignalSpy>
#include "../src/dialog.h"

class Test: public QObject {
    Q_OBJECT;
private:
    Dialog *dialog;

public:
    Test();
    ~Test();

private slots:
    void checkSignalOfSetButton();
    void timeOfFirstTimer();
    void timeOfSecondTimer();
};

#endif
