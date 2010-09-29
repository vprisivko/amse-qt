#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLocale>
#include <QString>
#include "timers.h"


Timers::Timers(QWidget *parent)
    : QDialog(parent){

	timerIds = new int[2];
	ticks = new int[2];

	for ( int i = 0; i < 2; ++i ){
		timerIds[i] = ticks[i] = 0;
	}

	curTimerIndex = 0;

	QLayout *l, *l1;
	QPushButton *pb;
	QComboBox *cb;

	l = new QVBoxLayout(this);
	setLayout(l);

	l1 = new QHBoxLayout();
	l1->addWidget(new QLabel("Timer 1: ", this));
	lab1 = new QLabel("0", this);
	l1->addWidget( lab1 );
	l->addItem(l1);

	l1 = new QHBoxLayout();
	l1->addWidget(new QLabel("Timer 2: ", this));
	lab2 = new QLabel("0", this);
	l1->addWidget( lab2 );
	l->addItem(l1);

	cb = new QComboBox(this);
	connect(cb, SIGNAL(currentIndexChanged(int)), this, SLOT(cBoxChanged(int)) );
	l->addWidget(cb);
	cb->addItem("Timer 1");
	cb->addItem("Timer 2");

	l1 = new QHBoxLayout();
	pb = new QPushButton("Set", this);
	connect(pb, SIGNAL(clicked()), this, SLOT(setBtnClk()) );
	lEd = new QLineEdit("0", this);
	l1->addWidget(lEd);
	l1->addWidget(pb);
	l->addItem(l1);

	pb = new QPushButton("Stop", this);
	connect(pb, SIGNAL(clicked()), this, SLOT(stopBtnClk()) );
	l->addWidget( pb );
	this->setWindowTitle("Tick. Tick. Tick. Ti...");

}


Timers::~Timers()
{
	delete[] timerIds;
	delete[] ticks;
}


void Timers::cBoxChanged(int index){
	curTimerIndex = index;
}


void Timers::timerEvent( QTimerEvent *e ){

	if ( timerIds[0] == e->timerId() ){
		ticks[0]++;
		lab1->setText( QString::number(ticks[0]) );
	}
	if ( timerIds[1] == e->timerId() ){
		ticks[1]++;
		lab2->setText( QString::number(ticks[1]) );
	}

}


void Timers::setBtnClk(){
	if ( timerIds[curTimerIndex] ){
		killTimer(timerIds[curTimerIndex]);
	}
	timerIds[curTimerIndex] = startTimer( lEd->text().toInt() );
}


void Timers::stopBtnClk(){
	if ( timerIds[curTimerIndex] ){
		killTimer(timerIds[curTimerIndex]);
	}
}



