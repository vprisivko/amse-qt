#ifndef TESTTIMERS_H
#define TESTTIMERS_H

#include <Qt>
#include <QTest>
#include <QSignalSpy>
#include "../src/timers.h"

class TestTimers : public QObject
{
    Q_OBJECT

    Dialog * m_dialog;

public:
    TestTimers();
    ~TestTimers() {}

private slots:
	void testFirstTimer();
	void testSecondTimer();
};

#endif // TESTTIMERS_H
