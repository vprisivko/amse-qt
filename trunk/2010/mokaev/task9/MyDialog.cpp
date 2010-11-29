#include <QHBoxLayout>
#include <QVBoxLayout>

#include "MyDialog.h"

MyDialog :: MyDialog( QWidget* parent ) : 
	QDialog( parent ),
        timerId( 0 ),
	count1( 0 ), count2( 0 ),
	isT1Exist( false ), isT2Exist( false )
{
    setWindowTitle( tr( "Simple Dialog" ) );

    mutex1 = new QMutex();
    mutex2 = new QMutex();

    createWidgets();
    addWidgets();
    setConnection();

    timerId = startTimer( DEFAULT_TIMER_VALUE );
} 

void MyDialog :: createWidgets(){
    t1Value = new QLCDNumber( this );
    t2Value = new QLCDNumber( this );
    timerComboBox = new QComboBox( this );
    timerComboBox->addItem( "timer 1" );
    timerComboBox->addItem( "timer 2" );
    timerEditBox = new QLineEdit( this );
    setButton = new QPushButton( "SET", this );
    stopButton = new QPushButton( "STOP", this );
}

void MyDialog :: addWidgets(){
    setLayout( new QVBoxLayout( this ) );

    QVBoxLayout* timersLayout = new QVBoxLayout;

    QHBoxLayout* timer1Layout = new QHBoxLayout;
    timer1Layout->addWidget( new QLabel( "<i>timer 1 : </i>", this ) );
    timer1Layout->addWidget( t1Value );

    QHBoxLayout* timer2Layout = new QHBoxLayout;
    timer2Layout->addWidget( new QLabel( "<i>timer 2 : </i>", this ) );
    timer2Layout->addWidget( t2Value );

    timersLayout->addItem( timer1Layout );
    timersLayout->addItem( timer2Layout );
    layout()->addItem( timersLayout );

    layout()->addWidget( timerComboBox );

    QHBoxLayout* timerSetLayout = new QHBoxLayout;
    timerSetLayout->addWidget( timerEditBox );
    timerSetLayout->addWidget( setButton );
    layout()->addItem( timerSetLayout );

    layout()->addWidget( stopButton );

}

void MyDialog :: setConnection(){
    connect( setButton, SIGNAL( clicked() ), this, SLOT( setClick() ) );
    connect( stopButton, SIGNAL( clicked() ), this, SLOT( stopClick() ) );
}

void MyDialog :: killThreadTimer( Timer* timer ){
    timer->terminate();
    timer->wait();
    delete timer;
}

void MyDialog :: setClick(){
    bool isNum = true;
    int value = timerEditBox->text().toInt( &isNum );
    if( !isNum ) {
        QMessageBox :: critical( this, "Simple Dialog", "Invalid Input Value" );
        return;
    }
    if( timerComboBox->currentIndex() == 0) {
        if( isT1Exist ){
            killThreadTimer( timer1 );
        }
        timer1 = new Timer( &count1, value, mutex1 );
        timer1->start();
        isT1Exist = true;
    } else {
        if( isT2Exist ){
            killThreadTimer( timer2 );
        }
        timer2 = new Timer( &count2, value, mutex2 );
        timer2->start();
        isT2Exist = true;
    }
}

void MyDialog :: stopClick(){
    if( timerComboBox->currentIndex() == 0 && isT1Exist ) {
        killThreadTimer( timer1 );
        isT1Exist = false;
    } else if( timerComboBox->currentIndex() == 1 && isT2Exist ) {
        killThreadTimer( timer2 );
        isT2Exist = false;
    }
}

void MyDialog :: timerEvent( QTimerEvent* e ){
    if( e->timerId() == timerId ) {
        mutex1->lock();
        t1Value->display( count1 );
        mutex1->unlock();

        mutex2->lock();
        t2Value->display( count2 );
        mutex2->unlock();
    }
}
