#include"Calculator.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
Calculator::Calculator(double res,QWidget *parent) : QDialog(parent) {
    result = res;
    createButtons();
    addButtons();
    connectButtons();
     this->show();
    setVisible(false);
}
void Calculator::createButtons() {
     plus = new QPushButton("+",this);
     minus = new QPushButton("-",this);
     times = new QPushButton("*",this);
     divide = new QPushButton("/",this);
     inputLine = new QLineEdit(this);
}

void Calculator::addButtons() {
    this->setLayout(new QVBoxLayout());
    this->layout()->addWidget(inputLine);
    QHBoxLayout *buttonsLay = new QHBoxLayout();
    buttonsLay->addWidget(plus);
    buttonsLay->addWidget(minus);
    buttonsLay->addWidget(times);
    buttonsLay->addWidget(divide);
    this->layout()->addItem(buttonsLay);
}

void Calculator::connectButtons(){
    connect(plus,SIGNAL(clicked()),this,SLOT(plusOp()));
    connect(minus,SIGNAL(clicked()),this,SLOT(minusOp()));
    connect(times,SIGNAL(clicked()),this,SLOT(multOp()));
    connect(divide,SIGNAL(clicked()),this,SLOT(divOp()));
}

void Calculator::plusOp(){
    makeOperation('+');
}
void Calculator::minusOp(){
    makeOperation('-');
}
void Calculator::multOp(){
     makeOperation('*');
}
void Calculator::divOp(){
    makeOperation('/');
}

void Calculator::makeOperation(char c){
    double curValue;
    double prevRes = result;
    op = c;
    if(inputLine->text() == ""){
        return;
    }
    curValue = inputLine->text().toDouble();
    switch(c) {
    case '+':
        result += curValue;break;
    case '-':
        result -= curValue;break;

    case '*':
        result *= curValue;break;

    case '/':
        result /= curValue;break;
    default: break;
    }

    emit  newexpr(QString("%1 %2 %3 = %4").arg(prevRes).arg(op).arg(curValue).arg(result),result);
    op = ' ';
    inputLine->setText( "" );
}
