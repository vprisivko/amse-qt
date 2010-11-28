#ifndef _MYDIALOG_H_
#define _MYDIALOG_H_
#include<QDialog>
#include<QPushButton>
#include<QLineEdit>
#include<QLCDNumber>
#include<QComboBox>
#include<QTimer>
#include<QEvent>
#include<QLabel>
#include<QTimer>
#include "TimerThread.h"

class MyDialog: public QDialog {
Q_OBJECT;
public:
        QTimer *timer;
        TimerThread *timerTh1;
        TimerThread *timerTh2;
	int currentTimer;
	int currentTime1;
	int currentTime2;
	QLabel *timer1Label;
	QLabel *timer2Label;
	QLCDNumber *num1;
	QLCDNumber *num2;
	QComboBox *timerCombo;
	QPushButton *setButton;
	QPushButton *stopButton;
	QLineEdit *setLineEdit;	
	MyDialog();

public slots:
	void setValue();
	void stopTimer();
	void changeCurrentTimer();
        void timerEvent();

};
#endif //MYDIALOG

