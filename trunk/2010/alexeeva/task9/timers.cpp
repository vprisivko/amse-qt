#include "timers.h"

Dialog::Dialog(QWidget * parent)	:QDialog(parent)	{
	index = 0;

   	ticks = new int[2];
   	ticks[0] = ticks[1] = 0;

   	t_threads = new TimerThread[2];

   	locks = new QMutex[2];

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

    QComboBox * comboChooseTimer = new QComboBox(this);
    comboChooseTimer->addItem("Timer1");
    comboChooseTimer->addItem("Timer2");
    connect(comboChooseTimer, SIGNAL(currentIndexChanged(int)), this, SLOT(cbChange(int)));
    layout()->addWidget(comboChooseTimer);

    QPushButton * buttSet = new QPushButton("Set", this);

    editInterval = new QLineEdit("1000", this);

    QHBoxLayout * layEdit = new QHBoxLayout();
    layEdit->addWidget(editInterval);
    layEdit->addWidget(buttSet);
    layout()->addItem(layEdit);

    QPushButton * buttStop = new QPushButton("Stop", this);
    layout()->addWidget(buttStop);

    connect(buttSet, SIGNAL(clicked()), this, SLOT(set()));
    connect(buttStop, SIGNAL(clicked()), this, SLOT(stop()));

    startTimer(50);
}

void Dialog::cbChange(int curTmrIndx){
	index = curTmrIndx;
}

void Dialog::timerEvent(QTimerEvent *){
    locks[0].lock();
    labValue1->setText(QString::number(ticks[0]));
    locks[0].unlock();

    locks[1].lock();
    labValue2->setText(QString::number(ticks[1]));
    locks[1].unlock();
}

void Dialog::stop(){
	if(t_threads[index].isRunning()){
		t_threads[index].terminate();
	}
}

void Dialog::set(){
	if(!editInterval->text().isEmpty()){

		if(t_threads[index].isRunning()){
			t_threads[index].terminate();
		}
		t_threads[index].set(editInterval->text().toInt(), &ticks[index], &locks[index]);
		t_threads[index].start();
	}
}

