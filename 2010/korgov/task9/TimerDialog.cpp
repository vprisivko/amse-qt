#include "TimerDialog.h"

TimerDialog::TimerDialog(QWidget *parent)
    : QDialog(parent), myTimer1(new Timer(this)), myTimer2(new Timer(this))
{
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
	myIntervalInput->setValidator(new QIntValidator(0,INT_MAX,this));
	setIntervalLayout->addWidget(myIntervalInput);
	mySetButton = new QPushButton("Set",this);
	setIntervalLayout->addWidget(mySetButton);
	this->layout()->addItem(setIntervalLayout);

	myStopButton = new QPushButton("Stop", this);
	this->layout()->addWidget(myStopButton);

	QObject::connect(mySetButton, SIGNAL(clicked()), this, SLOT(Set()));
	QObject::connect(myStopButton, SIGNAL(clicked()), this, SLOT(Stop()));

	startTimer(20);
}

TimerDialog::~TimerDialog()
{
}

void TimerDialog::Set()
{
	if(!myIntervalInput->text().isEmpty()){
		switch(myComboBox->currentIndex()){
			case 0: {
				restartTimer(myTimer1,myIntervalInput->text().toInt(),myTimer1ValueLabel->text().toInt());
			}break;
			case 1: {
				restartTimer(myTimer2,myIntervalInput->text().toInt(),myTimer2ValueLabel->text().toInt());
			}break;
		}
	}
}


void TimerDialog::Stop()
{
	switch(myComboBox->currentIndex()){
		case 0: {
			stopTimer(myTimer1);
		}break;
		case 1: {
			stopTimer(myTimer2);
		}break;
	}
}

void TimerDialog::restartTimer(Timer* timer, int interval, int startValue)
{
    timer->setAll(interval, startValue);
    timer->start();
}

void TimerDialog::stopTimer(Timer* timer)
{
    timer->terminate();
}

void TimerDialog::timerEvent(QTimerEvent *)
{
    if(myTimer1 != 0){
        myTimer1->getMutex()->lock();
        myTimer1ValueLabel->setText(QString::number(myTimer1->getCounter()));
        myTimer1->getMutex()->unlock();
    }

    if(myTimer2 != 0){
        myTimer2->getMutex()->lock();
        myTimer2ValueLabel->setText(QString::number(myTimer2->getCounter()));
        myTimer2->getMutex()->unlock();
    }
}
