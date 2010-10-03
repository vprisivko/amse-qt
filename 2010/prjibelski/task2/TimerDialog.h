#ifndef _TIMER_DIALOG_H_
#define _TIMER_DIALOG_H_

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLCDNumber>
#include <QComboBox>
#include <QTimer>
#include <QEvent>
#include <QLabel>


class TimerDialog: public  QDialog {
Q_OBJECT;

public:
	TimerDialog();

	/* Timer data */
	unsigned short currentTimer;
	unsigned int currentTime1;
	unsigned int currentTime2;
	unsigned int timer1Period;
	unsigned int timer2Period;
	int timer1Id;
	int timer2Id;

	/* GUI elemets for displaying time */
	QLabel * timer1Label;
	QLabel * timer2Label;
	QLCDNumber * currentTime1Number;
	QLCDNumber * currentTime2Number;

	/* GUI */
	QComboBox * timerComboBox;
	QPushButton * setPeriodButton;
	QPushButton * stopTimerButton;
	QLineEdit * periodLineEdit;	

	void timerEvent( QTimerEvent *e );

public slots:
	void setPeriod();
	void stopTimer();
	void changeCurrentTimer();

};

#endif /* _TIMER_DIALOG_H_ */
