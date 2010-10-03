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

class Dialog: public QDialog {

	Q_OBJECT;

public:
	Dialog(QWidget *parent = 0);
	void timerEvent(QTimerEvent *e);

public slots:
	void setInterval();
	void stopTimer();

private:
	int myTimer1_id, myTimer2_id;
	int myTicks1, myTicks2;
	bool isStopped1, isStopped2;

	QComboBox *myCBTimers;
	QLCDNumber *myTicker1, *myTicker2;
	QPushButton *myButtonSet;
	QPushButton *myButtonStop;
	QLineEdit *myEditInterval;

};

#endif //_TIMERS_DIALOG_H_
