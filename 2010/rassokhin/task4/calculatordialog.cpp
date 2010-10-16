#include "calculatordialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDoubleValidator>


CalculatorDialog::CalculatorDialog(QWidget *parent): QDialog(parent),
        lastResult(0) {
    setWindowTitle(tr("Calculator with log"));

    //generating
    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    QHBoxLayout * buttonsLayout = new QHBoxLayout();

    numberInput = new QLineEdit(this);
    QDoubleValidator * inputValidator = new QDoubleValidator( numberInput);
    numberInput->setValidator( inputValidator);

    QPushButton * plusB = new QPushButton("+",this);
    QPushButton * minusB = new QPushButton("-",this);
    QPushButton * multiplyB = new QPushButton("*",this);
    QPushButton * divideB = new QPushButton("/",this);

    //positioning
    mainLayout->addWidget( numberInput);
    mainLayout->addLayout( buttonsLayout);
    buttonsLayout->addWidget( plusB);
    buttonsLayout->addWidget( minusB);
    buttonsLayout->addWidget( multiplyB);
    buttonsLayout->addWidget( divideB);

    //connecting
    connect(plusB,SIGNAL(     clicked() ),SLOT( plus() ));
    connect(minusB,SIGNAL(    clicked() ),SLOT( minus() ));
    connect(multiplyB,SIGNAL( clicked() ),SLOT( multiply() ));
    connect(divideB,SIGNAL(   clicked() ),SLOT( divide() ));
    connect(plusB,SIGNAL(     clicked() ), numberInput, SLOT( setFocus() ));
    connect(minusB,SIGNAL(    clicked() ), numberInput, SLOT( setFocus() ));
    connect(multiplyB,SIGNAL( clicked() ), numberInput, SLOT( setFocus() ));
    connect(divideB,SIGNAL(   clicked() ), numberInput, SLOT( setFocus() ));
}

void CalculatorDialog::setLastOpResult(qreal lr) {
    lastResult = lr;
}

void CalculatorDialog::processResult(qreal newValue, QString opSymbol) {
    emit calculated( QString::number( lastResult ).append(" ").append( opSymbol)
                    .append(" ").append( QString::number( operand ) )
                    .append(" = ").append( QString::number( newValue ) ),
                    newValue);
    lastResult = newValue;
}

void CalculatorDialog::plus() {
    getop();
    processResult(lastResult + operand, "+");
}

void CalculatorDialog::minus() {
    getop();
    processResult(lastResult - operand, "-");
}

void CalculatorDialog::multiply() {
    getop();
    processResult(lastResult * operand, "*");
}

void CalculatorDialog::divide() {
    getop();
    if(operand==0) return;
    processResult(lastResult / operand, "/");
}

void CalculatorDialog::getop() {
    QString num = numberInput->text();
    operand = num.toDouble();
}
