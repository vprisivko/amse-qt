#ifndef TIMERDIALOGTEST_H
#define TIMERDIALOGTEST_H

#include <QObject>
#include "../src/TimerDialog.h"

class TimerDialogTest : public QObject {
	Q_OBJECT

private:
	TimerDialog *timerDialog;

private slots:
	void initTestCase();
	void comboBoxTest();
	void stopButtonClickTest();
	void setButtonClickTest();
	void testTimer1();
	void testTimer2();
	void cleanupTestCase();
};

#endif
