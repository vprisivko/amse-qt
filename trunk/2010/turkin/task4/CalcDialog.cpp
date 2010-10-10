#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QIntValidator>

#include "CalcDialog.h"

CalcDialog::CalcDialog(QWidget *parent): QDialog(parent) {

    // create interface
   
	setWindowTitle("calculator");

    QVBoxLayout* mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
        
	leDigits = new QLineEdit("");
	leDigits->setValidator( new QIntValidator() );
	mainLayout->addWidget( leDigits );

	QHBoxLayout* operLayout = new QHBoxLayout();
	btnPlus = new QPushButton("+");
	btnMinus = new QPushButton("-");
	btnMultiply = new QPushButton("*");
	btnDivide = new QPushButton("/");
	operLayout->addWidget(btnPlus);
	operLayout->addWidget(btnMinus);
	operLayout->addWidget(btnMultiply);
	operLayout->addWidget(btnDivide);

	mainLayout->addLayout(operLayout);
    
    // make connects
    
    connect( btnPlus, SIGNAL(clicked()), this, SLOT( plus()) );
    connect( btnMinus, SIGNAL(clicked()), this, SLOT(minus() ) );
	connect( btnMultiply, SIGNAL(clicked()), this, SLOT(multiply() ) );
	connect( btnDivide, SIGNAL(clicked()), this, SLOT(divide()) );

    
    // class fields initialization
	
	curResult = 0;
	curOperation = ' ';
}

void CalcDialog::plus() {
	makeOperation( '+' );
}
void CalcDialog::minus() {
	makeOperation( '-' );
}
void CalcDialog::multiply() {
	makeOperation( '*' );
}
void CalcDialog::divide() {
	makeOperation( '/' );
}

void CalcDialog::setResult(int result) {
    leDigits->setText( QString::number(result) );
    leDigits->setReadOnly(true);
    curOperation = ' ';
}

void CalcDialog::makeOperation(char op) {
	int digits1 = curResult;	
	int digits2 = leDigits->text().toInt();
	switch (curOperation) {
		case '+': 	
				curResult += digits2;
				break;
		case '-': 
				curResult -= digits2;	
				break;
		case '*': 
				curResult *= digits2; 
				break;
		case '/': 
				curResult /= digits2;   
				break;
		case ' ': 	
				curResult = digits2;		
				break;
	}
	leDigits->setText( "" );
	
	if (curOperation != ' ') {
		emit expr( QString("%1 %2 %3 = %4").arg(digits1).arg(curOperation).arg(digits2).arg(curResult), curResult);
	}

	curOperation = op;
	leDigits->setReadOnly(false);
}
