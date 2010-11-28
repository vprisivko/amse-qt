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

#include "threadtimer.h"

class TimerDialog: public  QDialog {
Q_OBJECT;

public:
	TimerDialog();

private:
        static const unsigned int timerPeriod = 10;

        /* Timer data */
        int currentTimer;
	unsigned int currentTime1;
	unsigned int currentTime2;

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

        QTimer* queryTimer;

        ThreadTimer* timer1;
        ThreadTimer* timer2;

        void createDialog();
        void connectSlots();

public:
        void timerEvent( QTimerEvent * );

public slots:
	void setPeriod();
	void stopTimer();
	void changeCurrentTimer();

};

#endif /* _TIMER_DIALOG_H_ */
