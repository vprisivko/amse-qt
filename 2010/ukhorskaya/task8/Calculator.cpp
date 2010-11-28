#include "Calculator.h"
#include "QMenuBar"
#include "QStatusBar"
#include "QMenu"
#include "QDebug"
#include "QVBoxLayout"
#include "QPushButton"
#include "QHBoxLayout"
#include "QFile"
#include "QFileDialog"
#include "QMessageBox"
#include "QScrollArea"

Calculator::Calculator(QWidget *parent): QDialog(parent)
{
    this->setMinimumSize(200, 100);

    createCalculator();

    lastValue = 0;
}

void Calculator::createCalculator() {
    this->setLayout(new QVBoxLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    lineEdit = new QLineEdit("0", this);
    this->layout()->addWidget(lineEdit);

    QPushButton *addButton = new QPushButton("+", this);
    addButton->setObjectName("+");
    QPushButton *subButton = new QPushButton("-", this);
    subButton->setObjectName("-");
    QPushButton *multiplyButton = new QPushButton("*", this);
    multiplyButton->setObjectName("*");
    QPushButton *divideButton = new QPushButton("/", this);
    divideButton->setObjectName("/");
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(subButton);
    buttonLayout->addWidget(multiplyButton);
    buttonLayout->addWidget(divideButton);

    this->layout()->addItem(buttonLayout);

    connect(addButton, SIGNAL(pressed()), this, SLOT(calcButtonPressed()));
    connect(subButton, SIGNAL(pressed()), this, SLOT(calcButtonPressed()));
    connect(multiplyButton, SIGNAL(pressed()), this, SLOT(calcButtonPressed()));
    connect(divideButton, SIGNAL(pressed()), this, SLOT(calcButtonPressed()));
}


void Calculator::calcButtonPressed() {
   QString objectName = sender()->objectName();

   //Divide on "0"
   if ((lineEdit->text().toDouble() == 0) && (objectName.compare("/") == 0)) {
       QMessageBox *error = new QMessageBox(this);
       error->warning(this, "Error", "Action is impossible");
       return;
   }
    QString text = "";
   text += QString().number(lastValue) + " " + objectName + " " + lineEdit->text() + " = ";
    if (objectName.compare("+") == 0) {
        lastValue += lineEdit->text().toDouble();
    } else if (objectName.compare("-") == 0) {
        lastValue -= lineEdit->text().toDouble();
    } else if (objectName.compare("*") == 0) {
        lastValue *= lineEdit->text().toDouble();
    } else if (objectName.compare("/") == 0) {
        lastValue /= lineEdit->text().toDouble();
    }

    text += QString().number(lastValue) + "\n";
//    centralLabel->setText(fileContent);

//    resultLabel->setText(QString().number(lastValue));
    lineEdit->setText("0");

    emit exprCalc(text);

    if(QString().number(lastValue) == "nan") {
        lastValue = 0;
    }
}
