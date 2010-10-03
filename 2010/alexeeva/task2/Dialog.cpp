#include "Dialog.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>

Dialog::Dialog(QWidget * parent)	:QDialog(parent)	{

   	timers_id = new int[2];
   	ticks = new int[2];
   	ticks[0] = ticks[1] = 0;

   	setLayout(new QVBoxLayout);

   	QHBoxLayout * layTimer1 = new QHBoxLayout();
    layTimer1->setAlignment(Qt::AlignCenter);
   	QLabel * labTimer1 = new QLabel("Timer1:", this);
   	labValue1 = new QLabel("0", this);
    labValue1->setAlignment(Qt::AlignRight);
   	layTimer1->addWidget(labTimer1);
   	layTimer1->addWidget(labValue1);
   	layout()->addItem(layTimer1);

    QHBoxLayout * layTimer2 = new QHBoxLayout();
    QLabel * labTimer2 = new QLabel("Timer 2:", this);
    labValue2 = new QLabel("0", this);
    labValue2->setAlignment(Qt::AlignRight);
    layTimer2->addWidget(labTimer2);
    layTimer2->addWidget(labValue2);
    layout()->addItem(layTimer2);

    QComboBox * comboChooseTimer = new QComboBox(this);
    connect(comboChooseTimer, SIGNAL(currentIndexChanged(int)), this, SLOT(cbChange(int)));
    comboChooseTimer->addItem("Timer1");
    comboChooseTimer->addItem("Timer2");
    layout()->addWidget(comboChooseTimer);

    QPushButton * buttSet = new QPushButton("Set", this);
    connect(buttSet, SIGNAL(clicked()), this, SLOT(set()));
    editInterval = new QLineEdit("1000", this);
    QHBoxLayout * layEdit = new QHBoxLayout();
    layEdit->addWidget(editInterval);
    layEdit->addWidget(buttSet);
    layout()->addItem(layEdit);

    QPushButton * buttStop = new QPushButton("Stop", this);
    connect(buttStop, SIGNAL(clicked()), this, SLOT(stop()));
    layout()->addWidget(buttStop);
}

Dialog::~Dialog(){
   	delete[] ticks;
   	delete[] timers_id;
}

void Dialog::timerEvent(QTimerEvent *e){
    if (timers_id[0] == e->timerId()){
    	ticks[0]++;
    	labValue1->setText( QString::number(ticks[0]) );
    }
    if ( timers_id[1] == e->timerId() ){
    	ticks[1]++;
    	labValue2->setText( QString::number(ticks[1]) );
    }
}

void Dialog::cbChange(int index){
	curTmrIndx = index;
}

void Dialog::stop(){
	if (timers_id[curTmrIndx]){
		killTimer(timers_id[curTmrIndx]);
	}
}

void Dialog::set(){
	if (timers_id[curTmrIndx]){
		killTimer(timers_id[curTmrIndx]);
	}
    timers_id[curTmrIndx] = startTimer(editInterval->text().toInt());
}
