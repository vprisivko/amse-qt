#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTimerEvent>
#include "dialog.h"
#include <iostream>


Dialog::Dialog(QWidget *parent) : QDialog(parent),
	timer1_(0), timer2_(0),
	count1_(0), count2_(0),
	exst1_(false), exst2_(false)
{
	btnSet_ = new QPushButton("set", this);
	btnStop_ = new QPushButton("stop", this);
	trmTicker1_ = new QLCDNumber(this);
	trmTicker2_ = new QLCDNumber(this);
	cbTimer_ = new QComboBox(this);
	txtValue_ = new QLineEdit(this);

	setLayout(new QVBoxLayout());

	QVBoxLayout *lay0 = new QVBoxLayout();
	QHBoxLayout *lay = new QHBoxLayout();
	lay->addWidget(new QLabel("Timer 1: ", this));
	lay->addWidget(trmTicker1_);
	lay0->addItem(lay);

	lay = new QHBoxLayout();
	lay->addWidget(new QLabel("Timer 2: ", this));
	lay->addWidget(trmTicker2_);
	lay0->addItem(lay);

	layout()->addItem(lay0);

	cbTimer_->addItem("Timer 1");
	cbTimer_->addItem("Timer 2");
	layout()->addWidget(cbTimer_);

	QHBoxLayout *lay1 = new QHBoxLayout();
	lay1->addWidget(txtValue_);
	lay1->addWidget(btnSet_);
	layout()->addItem(lay1);

	layout()->addWidget(btnStop_);

	connect(btnSet_, SIGNAL(clicked()), this, SLOT(set_click()));
	connect(btnStop_, SIGNAL(clicked()), this, SLOT(stop_click()));

	setWindowTitle("why?");
}

void Dialog::timerEvent(QTimerEvent *e)
{
	if(e->timerId() == timer1_) {
		trmTicker1_->display(++count1_);
	} else if(e->timerId() == timer2_) {
		trmTicker2_->display(++count2_);
	}
}

void Dialog::set_click()
{
	//std::cout << "set" << std::endl;
	bool ok = true;
	int value = txtValue_->text().toInt(&ok);
	if(!ok) {
		QMessageBox::critical(this, "why?", "Invalid input");
		return;
	}
	if(cbTimer_->currentIndex() == 0) {
		if(exst1_) killTimer(timer1_);
		timer1_ = startTimer(value);
		exst1_ = true;
	} else {
		if(exst2_) killTimer(timer2_);
		timer2_ = startTimer(value);
		exst2_ = true;
	}
}

void Dialog::stop_click()
{
	if(cbTimer_->currentIndex() == 0 && exst1_) {
		killTimer(timer1_);
		exst1_ = false;
	} else if(exst2_) {
		killTimer(timer2_);
		exst2_ = false;
	}
}
