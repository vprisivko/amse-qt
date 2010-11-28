#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLCDNumber>
#include<QComboBox>
#include<iostream>

#include "TimerDialog.h"

TimerDialog::TimerDialog() {
        currentTime1 = 0;
        currentTime2 = 0;
        currentTimer = 1;
        timer1 = new ThreadTimer(&currentTime1);
        timer2 = new ThreadTimer(&currentTime2);

        createDialog();
        connectSlots();

        QObject::startTimer(timerPeriod);
}

void TimerDialog::createDialog() {
    timer1Label = new QLabel( "Timer #1: ", this );
    timer2Label = new QLabel( "Timer #2: ", this );
    currentTime1Number = new QLCDNumber( this );
    currentTime2Number = new QLCDNumber( this );

    timerComboBox = new QComboBox( this );
    timerComboBox->addItem( "Timer #1" );
    timerComboBox->addItem( "Timer #2" );
    setPeriodButton = new QPushButton( "Set", this );
    stopTimerButton = new QPushButton( "Stop", this );
    periodLineEdit = new QLineEdit( this );

    this->setLayout( new QVBoxLayout() );

    QHBoxLayout * timer1Layout = new QHBoxLayout();
    timer1Layout->addWidget( timer1Label );
    timer1Layout->addWidget( currentTime1Number );

    QHBoxLayout * timer2Layout = new QHBoxLayout();
    timer2Layout->addWidget( timer2Label );
    timer2Layout->addWidget( currentTime2Number );

    QHBoxLayout * controlLayout = new QHBoxLayout();
    controlLayout->addWidget( periodLineEdit );
    controlLayout->addWidget( setPeriodButton );

    this->layout()->addItem( timer1Layout );
    this->layout()->addItem( timer2Layout );
    this->layout()->addWidget( timerComboBox );
    this->layout()->addItem( controlLayout );
    this->layout()->addWidget( stopTimerButton );
}

void TimerDialog::connectSlots() {
    QObject::connect( setPeriodButton, SIGNAL( pressed() ), this, SLOT( setPeriod() ) );
    QObject::connect( stopTimerButton, SIGNAL( pressed() ), this, SLOT( stopTimer() ) );
    QObject::connect( timerComboBox, SIGNAL( activated(int) ), this, SLOT( changeCurrentTimer() ) );
}

void TimerDialog::setPeriod() {
	int newPeriod = periodLineEdit->text().toInt();
	if( currentTimer == 1) {
            timer1->setPeriod(newPeriod);
            timer1->start();
        }
	else {
            timer2->setPeriod(newPeriod);
            timer2->start();
	}
}


void TimerDialog::stopTimer() {
	if ( currentTimer == 1 ) {
            timer1->terminate();
        } else {
            timer2->terminate();
        }
}


void TimerDialog::changeCurrentTimer() {
    currentTimer = timerComboBox->currentIndex() + 1;
}


void TimerDialog::timerEvent( QTimerEvent * ) {
    timer1->timerMutex.lock();
    currentTime1Number->display( (int) currentTime1 );
    timer1->timerMutex.unlock();

    timer2->timerMutex.lock();
    currentTime2Number->display( (int) currentTime2 );
    timer2->timerMutex.unlock();
}
