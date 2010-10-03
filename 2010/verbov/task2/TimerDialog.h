#ifndef _TIMER_DIALOG_H_
#define _TIMER_DIALOG_H_

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QTimerEvent>

class TimerDialog : public QDialog {

	Q_OBJECT

public:
	TimerDialog(QWidget *parent = 0);
	void timerEvent(QTimerEvent *event);

public slots:
	void setTimer();
	void stopTimer();

private:
	QLabel *myFirstTimerLabel, *mySecondTimerLabel;
	QPushButton *mySetButton, *myStopButton;
	QLineEdit *myTimerIntervalLineEdit;
	QComboBox *myTimersList;
	int myFirstTimerID, mySecondTimerID;
	int myFirstTimerValue, mySecondTimerValue;
};

#endif // _TIMER_DIALOG_H_
