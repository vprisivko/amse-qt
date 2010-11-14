#ifndef _DIALOGWRAPPER_H_
#define _DIALOGWRAPPER_H_

#include "../src/dialog.h"


class DialogWrapper : public Dialog
{
	Q_OBJECT;

public:
	using Dialog::set_click;
	using Dialog::stop_click;
	using Dialog::cbTimer_;
	using Dialog::txtValue_;
	using Dialog::btnSet_;
	using Dialog::btnStop_;
	using Dialog::trmTicker1_;
	using Dialog::trmTicker2_;
	using Dialog::count1_;
	using Dialog::count2_;

public:
	DialogWrapper(QWidget *parent = 0);

signals:
	void timerEventSignal();

private:
	virtual void timerEvent(QTimerEvent *);
};

#endif
