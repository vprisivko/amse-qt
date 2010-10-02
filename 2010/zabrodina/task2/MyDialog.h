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
class MyDialog: public QDialog {
Q_OBJECT;
public:
	int timer_id;
	int timer_e;
	int currentTimer;
	int currentTime1;
	int currentTime2;
	int period1,period2;
	QLabel *timer1Label;
	QLabel *timer2Label;
	QLCDNumber *num1;
	QLCDNumber *num2;
	QComboBox *timerCombo;
	QPushButton *setButton;
	QPushButton *stopButton;
	QLineEdit *setLineEdit;	
	MyDialog();
	void timerEvent( QTimerEvent *e);
public slots:
	void setValue();
	void stopTimer();
	void changeCurrentTimer();

};
#endif //MYDIALOG

