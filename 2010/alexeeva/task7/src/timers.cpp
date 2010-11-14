#include "timers.h"

Dialog::Dialog(QWidget * parent)	:QDialog(parent)	{
	index = 0;

   	timers = new int[2];
   	timers[0] = timers[1] = 0;

   	ticks = new int[2];
   	ticks[0] = ticks[1] = 0;

   	setLayout(new QVBoxLayout);

   	QLabel * labTimer1 = new QLabel("Timer 1:", this);
   	labValue1 = new QLabel("0", this);
    labValue1->setAlignment(Qt::AlignRight);

   	QHBoxLayout * layTimer1 = new QHBoxLayout();
    layTimer1->addWidget(labTimer1);
   	layTimer1->addWidget(labValue1);
   	layout()->addItem(layTimer1);

    QLabel * labTimer2 = new QLabel("Timer 2:", this);
    labValue2 = new QLabel("0", this);
    labValue2->setAlignment(Qt::AlignRight);

    QHBoxLayout * layTimer2 = new QHBoxLayout();
    layTimer2->addWidget(labTimer2);
    layTimer2->addWidget(labValue2);
    layout()->addItem(layTimer2);

    comboChooseTimer = new QComboBox(this);
    comboChooseTimer->addItem("Timer1");
    comboChooseTimer->addItem("Timer2");
    connect(comboChooseTimer, SIGNAL(currentIndexChanged(int)), this, SLOT(cbChange(int)));
    layout()->addWidget(comboChooseTimer);

    buttSet = new QPushButton("Set", this);

    editInterval = new QLineEdit("1000", this);

    QHBoxLayout * layEdit = new QHBoxLayout();
    layEdit->addWidget(editInterval);
    layEdit->addWidget(buttSet);
    layout()->addItem(layEdit);

    buttStop = new QPushButton("Stop", this);
    layout()->addWidget(buttStop);

    connect(buttSet, SIGNAL(clicked()), this, SLOT(set()));
    connect(buttStop, SIGNAL(clicked()), this, SLOT(stop()));
}

Dialog::~Dialog(){
   	delete[] ticks;
   	delete[] timers;
}

void Dialog::cbChange(int curTmrIndx){
	index = curTmrIndx;
}

void Dialog::timerEvent(QTimerEvent *e){
    if (timers[0] == e->timerId()){
    	ticks[0]++;
    	labValue1->setText(QString::number(ticks[0]));
    }
    else if (timers[1] == e->timerId()){
    	ticks[1]++;
    	labValue2->setText(QString::number(ticks[1]));
    }
}

void Dialog::stop(){
	if(timers[index] !=0){
		killTimer(timers[index]);
		timers[index] = 0;
	}
}

void Dialog::set(){
	if(!editInterval->text().isEmpty()){

		if(timers[index] != 0){
			killTimer(timers[index]);
			timers[index] = 0;
		}
		timers[index] = startTimer(editInterval->text().toInt());
		emit isSet();
	}
}
