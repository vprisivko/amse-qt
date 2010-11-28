#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "Dialog.h"

Dialog::Dialog(QWidget *parent): QDialog(parent),
	myTicks1(0), myTicks2(0),
	myTimer1(0), myTimer2(0) {

	setWindowTitle("Timers tricking");
	myMutex1 = new QMutex();
	myMutex2 = new QMutex();

	createWidgets();
	addWidgets();
	setConnections();

	myTimer_id = startTimer(10);
}

void Dialog::createWidgets() {
	myButtonSet = new QPushButton("SET", this);
	myButtonStop = new QPushButton("STOP", this);

	myCBTimers = new QComboBox(this);
	myCBTimers->addItem("Timer_1");
	myCBTimers->addItem("Timer_2");

	myEditInterval = new QLineEdit(this);

	myTicker1 = new QLCDNumber(this);
	myTicker2 = new QLCDNumber(this);
}

void Dialog::addWidgets() {
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
}

void Dialog::setConnections() {
	connect(myButtonSet, SIGNAL(pressed()), this, SLOT(setInterval()));
	connect(myButtonStop, SIGNAL(pressed()), this, SLOT(stopTimer()));
}

void Dialog::timerEvent(QTimerEvent *e) {
	if (e->timerId() == myTimer_id) {
		myMutex1->lock();
		myTicker1->display(myTicks1);
		myMutex1->unlock();

		myMutex2->lock();
		myTicker2->display(myTicks2);
		myMutex2->unlock();
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
		if (myTimer1 != 0) {
			myTimer1->terminate();
			myTimer1->wait();
			delete myTimer1;
			myTimer1 = 0;
		}
		myTimer1 = new Timer(interval, &myTicks1, myMutex1);
		myTimer1->start();
	} else if (myCBTimers->currentIndex() == 1) {
		if (myTimer2 != 0) {
			myTimer2->terminate();
			myTimer2->wait();
			delete myTimer2;
			myTimer2 = 0;
		}
		myTimer2 = new Timer(interval, &myTicks2, myMutex2);
		myTimer2->start();
	}
}

void Dialog::stopTimer() {
	if (myCBTimers->currentIndex() == 0) {
		if (myTimer1 != 0) {
			myTimer1->terminate();
			myTimer1->wait();
			delete myTimer1;
			myTimer1 = 0;
		}
	} else if (myCBTimers->currentIndex() == 1) {
		if (myTimer2 != 0) {
			myTimer2->terminate();
			myTimer2->wait();
			delete myTimer2;
			myTimer2 = 0;
		}
	}
}

