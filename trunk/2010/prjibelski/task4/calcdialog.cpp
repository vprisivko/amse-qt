#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

#include "calcdialog.h"


CalcDialog::CalcDialog(QWidget *parent) :
    QDialog(parent)
{
    this->createDialog();

    currentValue = 0.0;

    connect( plusButton, SIGNAL(pressed()), this, SLOT(plusSlot()) );
    connect( minusButton, SIGNAL(pressed()), this, SLOT(minusSlot()) );
    connect( mulButton, SIGNAL(pressed()), this, SLOT(mulSlot()) );
    connect( divButton, SIGNAL(pressed()), this, SLOT(divSlot()) );
}

void CalcDialog::createDialog() {
    this->setLayout( new QVBoxLayout() );

    QHBoxLayout*  buttonLayout = new QHBoxLayout();
    plusButton = new QPushButton("+", this);
    buttonLayout->addWidget(plusButton);
    minusButton = new QPushButton("-", this);
    buttonLayout->addWidget(minusButton);
    divButton = new QPushButton("/", this);
    buttonLayout->addWidget(divButton);
    mulButton = new QPushButton("*", this);
    buttonLayout->addWidget(mulButton);

    QHBoxLayout*  lineLayout = new QHBoxLayout();
    numLine = new QLineEdit(this);
    lineLayout->addWidget(numLine);

    this->layout()->addItem(lineLayout);
    this->layout()->addItem(buttonLayout);
}

void CalcDialog::sendString(double arg1, double arg2, char operation) {
    emit newString(
            QString("%1 %2 %3 = %4").arg(arg1).arg(operation).arg(arg2).arg(currentValue),
            currentValue );

    numLine->setText("");
}

void CalcDialog::setCurrentValue(double value) {
    currentValue = value;
}

void CalcDialog::plusSlot() {
    double arg1 = currentValue;
    double arg2 = numLine->text().toDouble();
    currentValue = arg1 + arg2;

    sendString(arg1,arg2,'+');
}

void CalcDialog::minusSlot() {
    double arg1 = currentValue;
    double arg2 = numLine->text().toDouble();
    currentValue = arg1 - arg2;

    sendString(arg1,arg2,'-');
}

void CalcDialog::mulSlot() {
    double arg1 = currentValue;
    double arg2 = numLine->text().toDouble();
    currentValue = arg1 * arg2;

    sendString(arg1,arg2,'*');
}

void CalcDialog::divSlot() {
    double arg1 = currentValue;
    double arg2 = numLine->text().toDouble();

    if (arg2 != 0.0) {
        currentValue = arg1 / arg2;
        sendString(arg1,arg2,'/');
    }
}

