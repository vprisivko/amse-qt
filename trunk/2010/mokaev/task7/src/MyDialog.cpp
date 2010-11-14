#include "MyDialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>


MyDialog :: MyDialog( QWidget* parent ) : 
	QDialog( parent ),
	timer1Id( 0 ), timer2Id( 0 ),
	count1( 0 ), count2( 0 ),
	isT1Exist( false ), isT2Exist( false )
{
	setWindowTitle( tr( "Simple Dialog" ) );
	setLayout( new QVBoxLayout( this ) );
	
	QVBoxLayout* timersLayout = new QVBoxLayout;//( this );
	
	QHBoxLayout* timer1Layout = new QHBoxLayout;//( &timersLayout );
	t1Value = new QLCDNumber( this );
    	timer1Layout->addWidget( new QLabel( "<i>timer 1 : </i>", this ) );
    	timer1Layout->addWidget( t1Value );
    	
	QHBoxLayout* timer2Layout = new QHBoxLayout;//( &timersLayout );
	t2Value = new QLCDNumber( this );
    	timer2Layout->addWidget( new QLabel( "<i>timer 2 : </i>", this ) );
   	timer2Layout->addWidget( t2Value );

    	timersLayout->addItem( timer1Layout );
    	timersLayout->addItem( timer2Layout );
    	layout()->addItem( timersLayout );
	
	timerComboBox = new QComboBox( this );
	timerComboBox->addItem( "timer 1" );
	timerComboBox->addItem( "timer 2" );
	layout()->addWidget( timerComboBox );

	QHBoxLayout* timerSetLayout = new QHBoxLayout;//( this );
	timerEditBox = new QLineEdit( this );
	setButton = new QPushButton( "SET", this );
	timerSetLayout->addWidget( timerEditBox );
	timerSetLayout->addWidget( setButton );
	layout()->addItem( timerSetLayout );
	
	stopButton = new QPushButton( "STOP", this );
	layout()->addWidget( stopButton );

	connect( setButton, SIGNAL( clicked() ), this, SLOT( setClick() ) );
	connect( stopButton, SIGNAL( clicked() ), this, SLOT( stopClick() ) );
	
} 


void MyDialog :: setClick()
{
	bool isNum = true;
	int value = timerEditBox->text().toInt( &isNum );
	if( !isNum ) {
		QMessageBox :: critical( this, "Simple Dialog", "Invalid Input Value" );
		return;
	}
	if( timerComboBox->currentIndex() == 0) {
		if( isT1Exist ) killTimer( timer1Id );
		timer1Id = startTimer( value );
		isT1Exist = true;
	} else {
		if( isT2Exist ) killTimer( timer2Id );
		timer2Id = startTimer( value );
		isT2Exist = true;
	}
        emit setSignal();
}

void MyDialog :: stopClick()
{
	if( timerComboBox->currentIndex() == 0 && isT1Exist ) {
		killTimer( timer1Id );
		isT1Exist = false;
	} else if( isT2Exist ) {
		killTimer( timer2Id );
		isT2Exist = false;
	}
}

void MyDialog :: timerEvent( QTimerEvent* e )
{
	if( e->timerId() == timer1Id ) {
                t1Value->display( ++count1 );
	} else if( e->timerId() == timer2Id ) {
		t2Value->display( ++count2 );
	}
}
