#include "TimerDialog.h"

TimerDialog::TimerDialog(QWidget *parent)
    : QDialog(parent), myTimer1Id(0), myTimer2Id(0),
      myTimer1Value(0), myTimer2Value(0) {
	this->setLayout(new QVBoxLayout());

	QHBoxLayout *timer1ValueLyaout = new QHBoxLayout();
	timer1ValueLyaout->addWidget(new QLabel("timer1: ",this));
	myTimer1ValueLabel = new QLabel("0",this);
	timer1ValueLyaout->addWidget(myTimer1ValueLabel);
	this->layout()->addItem(timer1ValueLyaout);

	QHBoxLayout *timer2ValueLyaout = new QHBoxLayout();
	timer2ValueLyaout->addWidget(new QLabel("timer2: ",this));
	myTimer2ValueLabel = new QLabel("0",this);
	timer2ValueLyaout->addWidget(myTimer2ValueLabel);
	this->layout()->addItem(timer2ValueLyaout);

	myComboBox = new QComboBox(this);
	myComboBox->addItem("timer1");
	myComboBox->addItem("timer2");
	this->layout()->addWidget(myComboBox);

	QHBoxLayout *setIntervalLayout = new QHBoxLayout();
	myIntervalInput = new QLineEdit(this);
	setIntervalLayout->addWidget(myIntervalInput);
	mySetButton = new QPushButton("Set",this);
	setIntervalLayout->addWidget(mySetButton);
	this->layout()->addItem(setIntervalLayout);

	myStopButton = new QPushButton("Stop", this);
	this->layout()->addWidget(myStopButton);

	QObject::connect(mySetButton, SIGNAL(clicked()), this, SLOT(Set()));
	QObject::connect(myStopButton, SIGNAL(clicked()), this, SLOT(Stop()));
}

TimerDialog::~TimerDialog(){
}

void TimerDialog::Set(){
	if(!myIntervalInput->text().isEmpty()){
		switch(myComboBox->currentIndex()){
			case 0: {
				restartTimer(myTimer1Id,myIntervalInput->text().toInt());
			}break;
			case 1: {
				restartTimer(myTimer2Id,myIntervalInput->text().toInt());
			}break;
		}
	}
}

void TimerDialog::Stop(){
	switch(myComboBox->currentIndex()){
		case 0: {
			stopTimer(myTimer1Id);
		}break;
		case 1: {
			stopTimer(myTimer2Id);
		}break;
	}
}

void TimerDialog::restartTimer(int &timer, int interval){
	stopTimer(timer);
	timer = startTimer(interval);
}

void TimerDialog::stopTimer(int &timer){
	if(timer !=0){
		killTimer(timer);
		timer = 0;
	}
}

void TimerDialog::timerEvent(QTimerEvent *e){
	if(e->timerId() == myTimer1Id){
		myTimer1Value++;
		myTimer1ValueLabel->setText(QString::number(myTimer1Value));
	}
	else if (e->timerId() == myTimer2Id){
		myTimer2Value++;
		myTimer2ValueLabel->setText(QString::number(myTimer2Value));
	}
}
