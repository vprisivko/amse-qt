#ifndef _TIMERDIALOG_H_
#define _TIMERDIALOG_H_

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <timer.h>

class TimerDialog : public QDialog {
	Q_OBJECT;

public:
	TimerDialog(QWidget *parent = NULL);
	virtual void timerEvent(QTimerEvent *);

protected:
	void closeEvent(QCloseEvent *e);

public slots:
	void setPressed();
	void stopPressed();

private:
	Timer myTimer1, myTimer2;
	int valueTimer1, valueTimer2;
	QMutex myMutex1, myMutex2;
	QLabel *label1, *label2;
	QComboBox *myComboBox;
	QLineEdit *intervalEdit;
	QPushButton *setButton;
	QPushButton *stopButton;
};

#endif
