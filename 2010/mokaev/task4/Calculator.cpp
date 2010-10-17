#include "Calculator.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>

Calculator :: Calculator( QWidget* parent ) : QDialog( parent ){
	setWindowTitle( "Calculator" );		
  	setLayout( new QVBoxLayout() );
  	createLineEdit();
  	createButtons();
	addButtons();
	connectButtons();
	initMembers();
  	
}
void Calculator :: initMembers(){
	curResult = 0;
}
void Calculator :: createLineEdit(){
	myLineEdt = new QLineEdit( QString::number( 0 ), this );
  	myLineEdt->setAlignment( Qt::AlignRight );
  	layout()->addWidget( myLineEdt );
}
void Calculator :: createButtons(){
	myAddBtn = new QPushButton( "+", this );
  	mySubtrBtn = new QPushButton( "-", this );
  	myMultBtn = new QPushButton( "*", this );
  	myDivBtn = new QPushButton( "/", this );
}
void Calculator :: addButtons(){
	QHBoxLayout* hBoxLayout = new QHBoxLayout();
  	hBoxLayout->addWidget( myAddBtn );
  	hBoxLayout->addWidget( mySubtrBtn );
  	hBoxLayout->addWidget( myMultBtn );
  	hBoxLayout->addWidget( myDivBtn );
  	layout()->addItem( hBoxLayout );
}
void Calculator :: connectButtons(){
	connect( myAddBtn, SIGNAL( clicked() ), this, SLOT( add() ) );
  	connect( mySubtrBtn, SIGNAL( clicked() ), this, SLOT( subtract() ) );
  	connect( myMultBtn, SIGNAL( clicked() ), this, SLOT( multiply() ) );
  	connect( myDivBtn, SIGNAL( clicked() ), this, SLOT( divide() ) );
}
void Calculator :: calcOperation( char operation ){    	
    	if( myLineEdt->text() == "" ){
        	return;
    	}

	double prevRes = curResult;
    	double newNumber = myLineEdt->text().toDouble();
    	
	switch( operation ) {
    		case '+':
        		curResult += newNumber;
			break;
    		case '-':
        		curResult -= newNumber;
			break;
    		case '*':
        		curResult *= newNumber;
			break;
    		case '/':
        		curResult /= newNumber;
			break;
    		default: break;
    	}

    	emit  newExpr( QString("%1 %2 %3 = %4").arg( prevRes ).arg( operation ).arg( newNumber ).arg( curResult ), curResult );
    	myLineEdt->setText( QString::number( 0 ) );	
}

void Calculator :: add(){
	calcOperation('+');
}



void Calculator :: subtract(){
	calcOperation('-');
}


void Calculator :: multiply(){
	calcOperation('*');
}


void Calculator :: divide(){
	calcOperation('/');
}

