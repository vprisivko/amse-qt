#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "Dialog.h"

Dialog::Dialog(QWidget *parent): QDialog(parent),
	myTimer1_id(0), myTimer2_id(0),
	myTicks1(0), myTicks2(0),
	isStopped1(true), isStopped2(true) {

	setWindowTitle("Timers tricking");

	myButtonSet = new QPushButton("SET", this);
	myButtonStop = new QPushButton("STOP", this);

	myCBTimers = new QComboBox(this);
	myCBTimers->addItem("Timer_1");
	myCBTimers->addItem("Timer_2");

	myEditInterval = new QLineEdit(this);

	myTicker1 = new QLCDNumber(this);
	myTicker2 = new QLCDNumber(this);

	setLayout(new QVBoxLayout(this));

	QHBoxLayout *lay = new QHBoxLayout();

	lay->addWidget(new QLabel("Timer 1: ", this));
	lay->addWidget(myTicker1);
	layout()->addItem(lay);

	lay = new QHBoxLayout();
	lay->addWidget(new QLabel("Timer 2: ", this));
	lay->addWidget(myTicker2);
	layout()->addItem(lay);

	layout()->addWidget(myCBTimers);

	lay = new QHBoxLayout();
	lay->addWidget(myEditInterval);
	lay->addWidget(myButtonSet);
	layout()->addItem(lay);

	layout()->addWidget(myButtonStop);

	connect(myButtonSet, SIGNAL(pressed()), this, SLOT(setInterval()));
	connect(myButtonStop, SIGNAL(pressed()), this, SLOT(stopTimer()));
}

void Dialog::timerEvent(QTimerEvent *e) {
	if (e->timerId() == myTimer1_id) {
		myTicker1->display(++myTicks1);
	} else if (e->timerId() == myTimer2_id) {
		myTicker2->display(++myTicks2);
	}
}

void Dialog::setInterval() {
	bool accepts = true;
	int interval = myEditInterval->text().toInt(&accepts);

	if (!accepts) {
		myEditInterval->setText("Invalid input!");
		return;
	}

	if (myCBTimers->currentIndex() == 0) {
		if (!isStopped1) {
			killTimer(myTimer1_id);
		}
		myTimer1_id = startTimer(interval);
		isStopped1 = false;
	} else if (myCBTimers->currentIndex() == 1) {
		if (!isStopped2) {
			killTimer(myTimer2_id);
		}
		myTimer2_id = startTimer(interval);
		isStopped2 = false;
	}
}

void Dialog::stopTimer() {
	if ((myCBTimers->currentIndex() == 0) && !isStopped1) {
		killTimer(myTimer1_id);
		isStopped1 = true;
	} else if ((myCBTimers->currentIndex() == 1) && !isStopped2) {
		killTimer(myTimer2_id);
		isStopped2 = true;
	}
}
