#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include "CalculatorDialog.h"

CalculatorDialog::CalculatorDialog(QWidget *parent) : QDialog(parent) {
	lastOperation = 0;

	setWindowTitle("Calculator");
	setLayout(new QVBoxLayout());

	createWidgets();
	fillLayout();
	connectSignalsAndSlots();
}

void CalculatorDialog::createWidgets() {
	inputLine = new QLineEdit("0", this);
	plusButton = new QPushButton("+", this);
	minusButton = new QPushButton("-", this);
	timesButton = new QPushButton("*", this);
	divideButton = new QPushButton("/", this);
}

void CalculatorDialog::fillLayout() {
	QHBoxLayout *buttonsLayout = new QHBoxLayout();
	buttonsLayout->addWidget(plusButton);
	buttonsLayout->addWidget(minusButton);
	buttonsLayout->addWidget(timesButton);
	buttonsLayout->addWidget(divideButton);

	layout()->addWidget(inputLine);
	layout()->addItem(buttonsLayout);
}

void CalculatorDialog::connectSignalsAndSlots() {
	connect(plusButton, SIGNAL(pressed()), this, SLOT(plus()));
	connect(minusButton, SIGNAL(pressed()), this, SLOT(minus()));
	connect(timesButton, SIGNAL(pressed()), this, SLOT(times()));
	connect(divideButton, SIGNAL(pressed()), this, SLOT(divide()));
}

void CalculatorDialog::setResult(double newResult) {
	result = newResult;
	lastOperation = 0;
	inputLine->setText(QString::number(result));
	emit resultChanged(result);
}

void CalculatorDialog::calculate(char operation) {
	double number = inputLine->text().toDouble();
	QString text = QString::number(result) + " " + lastOperation + " " + QString::number(number) + " = ";
	switch (lastOperation) {
		case '+':
			result += number;
			break;
		case '-':
			result -= number;
			break;
		case '*':
			result *= number;
			break;
		case '/':
			result /= number;
			break;
		default:
			result = number;
	}
	text += QString::number(result);
	inputLine->setText(QString::number(result));
	if (lastOperation) {
		emit addOperation(text);
	}
	emit resultChanged(result);
	lastOperation = operation;
}

void CalculatorDialog::plus() {
	calculate('+');
}

void CalculatorDialog::minus() {
	calculate('-');
}

void CalculatorDialog::times() {
	calculate('*');
}

void CalculatorDialog::divide() {
	calculate('/');
}
