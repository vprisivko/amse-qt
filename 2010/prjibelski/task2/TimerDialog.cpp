#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLCDNumber>
#include<QComboBox>

#include "TimerDialog.h"

TimerDialog::TimerDialog():
	currentTimer( 1 ), currentTime1( 0 ), currentTime2( 0 ), timer1Period( 0 ), timer2Period (0) {

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
	
	QObject::connect( setPeriodButton, SIGNAL( pressed() ), this, SLOT( setPeriod() ) );
	QObject::connect( stopTimerButton, SIGNAL( pressed() ), this, SLOT( stopTimer() ) );
	QObject::connect( timerComboBox, SIGNAL( activated(int) ), this, SLOT( changeCurrentTimer() ) );
}

void TimerDialog::setPeriod() {
	int newPeriod = periodLineEdit->text().toInt();
	if( currentTimer == 1) {
		QObject::killTimer( timer1Id );
		timer1Id = QObject::startTimer( newPeriod ); 
		timer1Period = newPeriod;
	}
	else {
		QObject::killTimer( timer2Id );
		timer2Id = QObject::startTimer( newPeriod ); 
		timer2Period = newPeriod;
	}
}


void TimerDialog::stopTimer() {
	if ( currentTimer == 1 ) {
		QObject::killTimer( timer1Id );
	} else {
		QObject::killTimer( timer2Id );
	}
}


void TimerDialog::changeCurrentTimer() {
	currentTimer = timerComboBox->currentIndex() + 1;
}


void TimerDialog::timerEvent( QTimerEvent *e ) {
	if( e->timerId() == timer1Id )	{
		currentTime1 += timer1Period;	
		currentTime1Number->display( (int) currentTime1 );	
	}
	else {
		currentTime2 += timer2Period;	
		currentTime2Number->display( (int) currentTime2 );	
	}
}
