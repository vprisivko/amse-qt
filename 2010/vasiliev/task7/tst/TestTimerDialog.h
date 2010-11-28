#ifndef _TEST_TIMER_DIALOG_H_
#define _TEST_TIMER_DIALOG_H_

#include <QTest>
#include <Qt>
#include <QSignalSpy>

#include "../src/TimerDialog.h"

class Tester: public QObject {

Q_OBJECT;

public:
	Tester();
	~Tester();

private slots:
	void testSignals();
	void testButtons();
	void testSemantic();

private:
	TimerDialog *myTimerDialog;	

};

#endif // _TEST_TIMER_DIALOG_H_
