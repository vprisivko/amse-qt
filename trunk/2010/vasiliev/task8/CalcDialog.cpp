#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIntValidator>

#include "CalcDialog.h"

CalcDialog::CalcDialog(QWidget *parent): QDialog(parent),
	myResult(0) {

	setWindowTitle("Calculation");
	setLayout(new QVBoxLayout(this));

	myPlusBtn = new QPushButton("+", this);
	myMinusBtn = new QPushButton("-",this);
	myMultiplyBtn = new QPushButton("*", this);
	myDivisionBtn = new QPushButton("/", this);

	myExpressionEdit = new QLineEdit(this);
	QIntValidator *inputValidator = new QIntValidator(this);
	myExpressionEdit->setValidator(inputValidator);

	QHBoxLayout *btnLay = new QHBoxLayout();

	layout()->addWidget(myExpressionEdit);

	btnLay->addWidget(myPlusBtn);
	btnLay->addWidget(myMinusBtn);
	btnLay->addWidget(myMultiplyBtn);
	btnLay->addWidget(myDivisionBtn);
	layout()->addItem(btnLay);

	QObject::connect(myPlusBtn, SIGNAL(clicked()), this, SLOT(add()));
	QObject::connect(myMinusBtn, SIGNAL(clicked()), this, SLOT(sub()));
	QObject::connect(myMultiplyBtn, SIGNAL(clicked()), this, SLOT(mul()));
	QObject::connect(myDivisionBtn, SIGNAL(clicked()), this, SLOT(div()));

}

void CalcDialog::setResult(int result) {
	myResult = result;
}

int CalcDialog::getResult() const {
	return myResult;
}

void CalcDialog::add() {
	doArythmethic('+');
}

void CalcDialog::sub() {
	doArythmethic('-');
}

void CalcDialog::mul() {
	doArythmethic('*');
}

void CalcDialog::div() {
	doArythmethic('/');
}

void CalcDialog::doArythmethic(const char &operation) {
	int leftSide = myResult;
	int rightSide = myExpressionEdit->text().toInt();
	bool wasDivisionByZero = false;
	switch(operation) {
	case '+': {
			myResult+=rightSide;
			break;
		}
	case '-': {
			myResult-=rightSide;
			break;
		}
	case '*': {
			myResult*=rightSide;
			break;
		}
	case '/': {
			if (rightSide == 0) {
				wasDivisionByZero = true;
				break;
			}
			myResult/=rightSide;
			break;
		}
	}

	if (wasDivisionByZero) {
		emit sendExpression("Was division by zero! Try to input another data!", myResult);
	} else {
		emit sendExpression(QString::number(leftSide) + " " + operation +
				" " + QString::number(rightSide) + " = " +
				QString::number(myResult), myResult);
	}
	myExpressionEdit->setText("");
}

