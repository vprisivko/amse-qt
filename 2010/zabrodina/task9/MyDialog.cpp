#include<stdio.h>
#include<QDebug>
#include<QVBoxLayout>
#include<QLCDNumber>
#include<QHBoxLayout>
#include<QComboBox>
#include"MyDialog.h"
MyDialog :: MyDialog() {
	setButton = new QPushButton( "SET", this );
	stopButton = new QPushButton( "STOP", this );
	timer1Label = new QLabel( "Timer1", this );
	timer2Label = new QLabel( "Timer2", this );
	setLineEdit = new QLineEdit( this );
	num1 = new QLCDNumber( this );
	num2 = new QLCDNumber( this );
	currentTime1 = 0;
	currentTime2 = 0;
        timerTh1=0;
        timerTh2=0;
	timerCombo = new QComboBox( this );
	timerCombo->addItem( "Timer1" );
	timerCombo->addItem( "Timer2" );
	currentTimer = 0;
	this->setLayout( new QVBoxLayout() );

	QHBoxLayout *timer1Layout = new QHBoxLayout();
	timer1Layout->addWidget( timer1Label );
	timer1Layout->addWidget( num1 );

        QHBoxLayout *timer2Layout = new QHBoxLayout();
	timer2Layout->addWidget( timer2Label );
	timer2Layout->addWidget( num2 );
	
	QHBoxLayout *setLayout = new QHBoxLayout();
	setLayout->addWidget( setLineEdit );
	setLayout->addWidget( setButton );

	this->layout()->addItem( timer1Layout );
	this->layout()->addItem( timer2Layout );
	this->layout()->addWidget( timerCombo );
	this->layout()->addItem( setLayout );
	this->layout()->addWidget( stopButton );
        timer = new QTimer(this);


	QObject::connect( setButton, SIGNAL( pressed() ), this, SLOT( setValue() ) );
	QObject::connect( stopButton, SIGNAL( pressed() ), this, SLOT( stopTimer() ) );
	QObject::connect( timerCombo, SIGNAL( activated(int) ), this, SLOT( changeCurrentTimer() ) );
        QObject::connect(timer,SIGNAL(timeout()),this,SLOT(timerEvent()));
        timer->start(10);
	
}
void MyDialog:: setValue() {
	int a = setLineEdit->text().toInt();
	if( currentTimer == 0) {
            if(timerTh1 != 0){
                timerTh1->terminate();
                timerTh1->wait();
                delete timerTh1;
                timerTh1 = 0;
            }
            timerTh1 = new TimerThread(a, &currentTime1 );
            timerTh1->start();

                //QObject::killTimer( timer_id ); timer_id = QObject::startTimer( a ); period1 = a;
	}
	else {
            if(timerTh2 != 0){
               timerTh2->terminate();
               timerTh2->wait();
                delete timerTh2;
                timerTh2 = 0;
            }
            timerTh2 = new TimerThread(a, &currentTime2 );
            timerTh2->start();
                //QObject::killTimer( timer_e ); timer_e = QObject::startTimer( a ); period2 = a;
	}
}

void MyDialog:: stopTimer() {
    if(currentTimer ==0 ){
        if(timerTh1 != 0){
         timerTh1->terminate();
         timerTh1->wait();
            delete timerTh1;
            timerTh1 = 0;
        }
    }
    else {
        if(timerTh2 != 0){
         timerTh2->terminate();
         timerTh2->wait();
            delete timerTh2;
            timerTh2 = 0;
        }

    }
        //currentTimer == 0 ? QObject::killTimer( timer_id ) : QObject::killTimer( timer_e );
}
void MyDialog:: changeCurrentTimer() {
	currentTimer = timerCombo->currentIndex();
}
void MyDialog:: timerEvent() {
    if(timerTh1 !=0 ){
    timerTh1->mutex.lock();
    num1->display( currentTime1 );
    timerTh1->mutex.unlock();
    }
    if(timerTh2 != 0){
    timerTh2->mutex.lock();
    num2->display( currentTime2 );
    timerTh2->mutex.unlock();
}
}


