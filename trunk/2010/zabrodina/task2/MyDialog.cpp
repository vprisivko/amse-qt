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
	period1 = 0;
	period2 = 0;
	currentTime2 = 0;
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
	
	QObject::connect( setButton, SIGNAL( pressed() ), this, SLOT( setValue() ) );
	QObject::connect( stopButton, SIGNAL( pressed() ), this, SLOT( stopTimer() ) );
	QObject::connect( timerCombo, SIGNAL( activated(int) ), this, SLOT( changeCurrentTimer() ) );
	
}
void MyDialog:: setValue() {
	int a = setLineEdit->text().toInt();
	if( currentTimer == 0) {
		QObject::killTimer( timer_id ); timer_id = QObject::startTimer( a ); period1 = a;
	}
	else {
		QObject::killTimer( timer_e ); timer_e = QObject::startTimer( a ); period2 = a; 
	}
}

void MyDialog:: stopTimer() {
	currentTimer == 0 ? QObject::killTimer( timer_id ) : QObject::killTimer( timer_e );
}
void MyDialog:: changeCurrentTimer() {
	currentTimer = timerCombo->currentIndex();
}
void MyDialog:: timerEvent( QTimerEvent *e ) {
	if( e->timerId() == timer_id )	{
		currentTime1 += period1;	
		num1->display( currentTime1 );	
	}
	else {
		currentTime2 += period2;	
		num2->display( currentTime2 );		
	}
}


