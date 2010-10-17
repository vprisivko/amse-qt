#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

#include "calcdialog.h"


CalcDialog::CalcDialog(QWidget *parent) :
    QDialog(parent)
{
    this->createDialog();

    currentValue = 0;

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

void CalcDialog::sendString(int arg1, int arg2, char operation) {
    emit newString(
            QString("%1 %2 %3 = %4").arg(arg1).arg(operation).arg(arg2).arg(currentValue),
            currentValue );

    numLine->setText("");
}

void CalcDialog::setCurrentValue(int value) {
    currentValue = value;
}

void CalcDialog::plusSlot() {
    int arg1 = currentValue;
    int arg2 = numLine->text().toInt();
    currentValue = arg1 + arg2;

    sendString(arg1,arg2,'+');
}

void CalcDialog::minusSlot() {
    int arg1 = currentValue;
    int arg2 = numLine->text().toInt();
    currentValue = arg1 - arg2;

    sendString(arg1,arg2,'-');
}

void CalcDialog::mulSlot() {
    int arg1 = currentValue;
    int arg2 = numLine->text().toInt();
    currentValue = arg1 * arg2;

    sendString(arg1,arg2,'*');
}

void CalcDialog::divSlot() {
    int arg1 = currentValue;
    int arg2 = numLine->text().toInt();

    if (arg2 != 0) {
        currentValue = arg1 / arg2;
        sendString(arg1,arg2,'/');
    }
}

