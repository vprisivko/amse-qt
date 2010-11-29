#include "Calculator.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIntValidator>

Calculator::Calculator(QWidget *parent) : QDialog(parent), myCurResult(0) {
    QVBoxLayout* mainLayout = new QVBoxLayout();
    setLayout(mainLayout);

    numberLineEdit = new QLineEdit("0");
    numberLineEdit->setValidator(new QIntValidator());
    mainLayout->addWidget(numberLineEdit);

    plusButton = new QPushButton("+");
    minusButton = new QPushButton("-");
    asterixButton = new QPushButton("*");
    slashButton = new QPushButton("/");

    QHBoxLayout* btnsLayout = new QHBoxLayout();
    btnsLayout->addWidget(plusButton);
    btnsLayout->addWidget(minusButton);
    btnsLayout->addWidget(asterixButton);
    btnsLayout->addWidget(slashButton);
    mainLayout->addLayout(btnsLayout);

    connect(plusButton, SIGNAL(clicked()), this, SLOT(sumUp()));
    connect(minusButton, SIGNAL(clicked()), this, SLOT(subtract()));
    connect(asterixButton, SIGNAL(clicked()), this, SLOT(multiply()));
    connect(slashButton, SIGNAL(clicked()), this, SLOT(divide()));
}

void Calculator::calculate(char str) {
    if(!numberLineEdit->text().isEmpty()){
        double num = myCurResult;
        switch (str) {
            case '+':
                myCurResult += numberLineEdit->text().toDouble();
                break;
            case '-':
                myCurResult -= numberLineEdit->text().toDouble();
                break;
            case '*':
                myCurResult *= numberLineEdit->text().toDouble();
                break;
            case '/':
                myCurResult /= numberLineEdit->text().toDouble();
                break;
        }
        emit toWrite(QString::number(num) + str + numberLineEdit->text() + " = " + QString::number(myCurResult), myCurResult);
    }
}

void Calculator::sumUp() {
    calculate('+');
}
void Calculator::subtract() {
    calculate('-');
}
void Calculator::multiply() {
    calculate('*');
}
void Calculator::divide() {
    calculate('/');
}
