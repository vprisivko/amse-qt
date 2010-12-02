#include "Calculator.h"
#include <QtGui>

Calculator :: Calculator(QWidget *parent) : QDialog(parent) {

	sum = 0.0;
	
	
	setWindowTitle("Magic Calculator");
	

	lineEdit = new QLineEdit;
	lineEdit->setValidator(new QDoubleValidator(lineEdit));

	plusButton = new QPushButton("+");
	minusButton = new QPushButton("-");
	multiplyButton = new QPushButton("*");
	divideButton = new QPushButton("/");
	plusButton->setEnabled(false);
	minusButton->setEnabled(false);
	multiplyButton->setEnabled(false);
	divideButton->setEnabled(false);

	QHBoxLayout *topLayout = new QHBoxLayout();
	topLayout->addWidget(plusButton);
	topLayout->addWidget(minusButton);
	topLayout->addWidget(multiplyButton);
	topLayout->addWidget(divideButton);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(lineEdit);
	mainLayout->addItem(topLayout);
	setLayout(mainLayout);

	connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableButton(const QString &)));
	connect(plusButton, SIGNAL(clicked()), this, SLOT(plus()));
	connect(minusButton, SIGNAL(clicked()), this, SLOT(minus()));
	connect(multiplyButton, SIGNAL(clicked()), this, SLOT(multiply()));
	connect(divideButton, SIGNAL(clicked()), this, SLOT(divide()));
}
void Calculator :: setSum(double sum) {
	this->sum = sum;
}
void Calculator :: plus() {
	QString str = QString :: number(sum);
	QString text = lineEdit->text();
	double number = text.toDouble();
	sum = sum + number;
	lineEdit->clear();
	str.append(" + ");
	str.append(QString :: number(number));
	send(str);
}
void Calculator :: minus() {
	QString str = QString :: number(sum);
	QString text = lineEdit->text();
	double number = text.toDouble();
	sum = sum - number;
	lineEdit->clear();
	str.append(" - ");
	str.append(QString :: number(number));
	send(str);
}
void Calculator :: multiply() {
	QString str = QString :: number(sum);
	QString text = lineEdit->text();
	double number = text.toDouble();
	sum = sum * number;
	lineEdit->clear();
	str.append(" * ");
	str.append(QString :: number(number));
	send(str);
}
void Calculator :: divide() {
	QString str = QString :: number(sum);
	QString text = lineEdit->text();
	double number = text.toDouble();
	if (number != 0) {
		sum = sum / number;
		lineEdit->clear();
		str.append(" / ");
		str.append(QString :: number(number));
		send(str);
	}
}
void Calculator :: send(QString &str) {
	str.append(" = ");
	str.append(QString :: number(sum));
	emit answer(str);
}
void Calculator :: enableButton(const QString &text) {
	plusButton->setEnabled(!text.isEmpty());
	minusButton->setEnabled(!text.isEmpty());
	multiplyButton->setEnabled(!text.isEmpty());
	divideButton->setEnabled(!text.isEmpty());
}








