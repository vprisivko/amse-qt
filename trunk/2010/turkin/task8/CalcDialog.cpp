#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QDoubleValidator>

#include "CalcDialog.h"

CalcDialog::CalcDialog(QWidget *parent): QDialog(parent) {
    setWindowTitle("calculator");
    setLayout( new QVBoxLayout() );
        
    createDigits();
    createButtons();
    createConnects();
    
    setResult(0);
}

void CalcDialog::createDigits() {
    leDigits = new QLineEdit("",this);
    leDigits->setValidator( new QDoubleValidator(this) );
    layout()->addWidget( leDigits );
}
	
void CalcDialog::createButtons() {
    QHBoxLayout* operLayout = new QHBoxLayout();
    btnPlus = new QPushButton("+",this);
    btnMinus = new QPushButton("-",this);
    btnMultiply = new QPushButton("*",this);
    btnDivide = new QPushButton("/",this);
    operLayout->addWidget(btnPlus);
    operLayout->addWidget(btnMinus);
    operLayout->addWidget(btnMultiply);
    operLayout->addWidget(btnDivide);
    layout()->addItem(operLayout);
}
	
void CalcDialog::createConnects() {
    connect( btnPlus, SIGNAL(clicked()), this, SLOT( plus()) );
    connect( btnMinus, SIGNAL(clicked()), this, SLOT(minus() ) );
    connect( btnMultiply, SIGNAL(clicked()), this, SLOT(multiply() ) );
    connect( btnDivide, SIGNAL(clicked()), this, SLOT(divide()) );
}

void CalcDialog::hideEvent( QHideEvent*  ) {
    emit calcHide(false);
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

void CalcDialog::setResult(double result) {
    myResult = result;
    leDigits->setText( QString::number(myResult) );
}

void CalcDialog::makeOperation(char op) {
        double value = leDigits->text().toDouble();
        double newResult = 0;
        switch (op) {
            case '+':
                newResult = myResult + value;
                break;
            case '-':
                newResult = myResult - value;
                break;
            case '*':
                newResult = myResult * value;
                break;
            case '/':
                if (value == 0) {
                    QMessageBox::critical(this,"Error!","Division on null error");
                    return;
                } else {
                     newResult = myResult / value;
                }
                break;
        }
	
        emit expr( myResult, op, value, newResult);
        myResult = newResult;

}
