#ifndef _TIMERS_DIALOG_H_
#define _TIMERS_DIALOG_H_

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
#include <QTimer>
#include <QEvent>
#include <QLCDNumber>
#include <QComboBox>

#include <QMutex>

#include "Timer.h"

class Dialog: public QDialog {

	Q_OBJECT;

public:
	Dialog(QWidget *parent = 0);
	void timerEvent(QTimerEvent *e);

public slots:
	void setInterval();
	void stopTimer();

private:
	int myTimer_id;

	int myTicks1, myTicks2;

	Timer *myTimer1;
	Timer *myTimer2;
	QMutex *myMutex1;
	QMutex *myMutex2;

	QComboBox *myCBTimers;
	QLCDNumber *myTicker1, *myTicker2;
	QPushButton *myButtonSet;
	QPushButton *myButtonStop;
	QLineEdit *myEditInterval;

private:
	void createWidgets();
	void addWidgets();
	void setConnections();

};

#endif //_TIMERS_DIALOG_H_
