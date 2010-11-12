#ifndef TIMERSTEST_H
#define TIMERSTEST_H

#include <QTest>
#include <QSignalSpy>

#include "../src/timersdialog.h"

class TimersTest : public QObject {
    Q_OBJECT;
public:
    TimersTest(QObject *parent = 0);


private slots:
    void initTestCase();
    void firstTimerTest();
    void secondTimerTest();
    void cleanupTestCase();

private:
    TimersDialog * m_dialog;

};

#endif // TIMERSTEST_H
