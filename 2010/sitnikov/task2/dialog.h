#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <QDialog>
#include <QPushButton>
#include <QLCDNumber>
#include <QComboBox>
#include <QLineEdit>


class Dialog : public QDialog
{
	Q_OBJECT;

public:
	Dialog(QWidget *parent = 0);

	virtual void timerEvent(QTimerEvent *);

private slots:
	void set_click();
	void stop_click();

private:
	int timer1_, timer2_;
	int count1_, count2_;
	bool exst1_, exst2_;
	QPushButton *btnSet_;
	QPushButton *btnStop_;
	QLCDNumber *trmTicker1_;
	QLCDNumber *trmTicker2_;
	QComboBox *cbTimer_;
	QLineEdit *txtValue_;
};

#endif
