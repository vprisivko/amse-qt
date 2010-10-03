#include <QVBoxLayout>
#include <QHBoxLayout>
#include "TimerDialog.h"

TimerDialog::TimerDialog(QWidget *parent) : QDialog(parent) {
	myFirstTimerID = mySecondTimerID = 0;
	myFirstTimerValue = mySecondTimerValue = 0;
	setLayout(new QVBoxLayout());
	
	myFirstTimerLabel = new QLabel("Timer 1: 0", this);
	mySecondTimerLabel = new QLabel("Timer 2: 0", this);
	myTimersList = new QComboBox(this);
	myTimersList->addItem("Timer 1");
	myTimersList->addItem("Timer 2");
	myTimerIntervalLineEdit = new QLineEdit("1000", this);
	mySetButton = new QPushButton("Set", this);
	myStopButton = new QPushButton("Stop", this);

	layout()->addWidget(myFirstTimerLabel);
	layout()->addWidget(mySecondTimerLabel);
	layout()->addWidget(myTimersList);
	QHBoxLayout *intervalLayout = new QHBoxLayout();
	intervalLayout->addWidget(myTimerIntervalLineEdit);
	intervalLayout->addWidget(mySetButton);
	layout()->addItem(intervalLayout);
	layout()->addWidget(myStopButton);

	connect(mySetButton, SIGNAL(pressed()),
		this, SLOT(setTimer()));
	connect(myStopButton, SIGNAL(pressed()),
		this, SLOT(stopTimer()));
}

void TimerDialog::timerEvent(QTimerEvent *event) {
	QString value;
	if (event->timerId() == myFirstTimerID) {
		myFirstTimerLabel->setText("Timer 1: " + value.setNum(++myFirstTimerValue));
	} else {
		mySecondTimerLabel->setText("Timer 2: " + value.setNum(++mySecondTimerValue));
	}
}

void TimerDialog::setTimer() {
	int interval = myTimerIntervalLineEdit->text().toInt();
	if (myTimersList->currentIndex() == 0) {
		killTimer(myFirstTimerID);
		myFirstTimerID = startTimer(interval);
	} else {
		killTimer(mySecondTimerID);
		mySecondTimerID = startTimer(interval);
	}
}

void TimerDialog::stopTimer() {
	killTimer(myTimersList->currentIndex() == 0 ? myFirstTimerID : mySecondTimerID);
}
