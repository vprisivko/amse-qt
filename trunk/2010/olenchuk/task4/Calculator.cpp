#include "Calculator.h"
#include <QtGui>

Calculator :: Calculator(QWidget *parent) : QDialog(parent) {

	sum = 0;
	
	
	setWindowTitle("Magic Calculator");
	

	lineEdit = new QLineEdit("");
	lineEdit->setValidator(new QIntValidator());

	QHBoxLayout* topLayout = new QHBoxLayout();
	plusButton = new QPushButton("+");
	minusButton = new QPushButton("-");
	multiplyButton = new QPushButton("*");
	divideButton = new QPushButton("/");
	topLayout->addWidget(plusButton);
	topLayout->addWidget(minusButton);
	topLayout->addWidget(multiplyButton);
	topLayout->addWidget(divideButton);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(lineEdit);
	mainLayout->addItem(topLayout);
	setLayout(mainLayout);

	connect(plusButton, SIGNAL(clicked()), this, SLOT(plus()));
	connect(minusButton, SIGNAL(clicked()), this, SLOT(minus()));
	connect(multiplyButton, SIGNAL(clicked()), this, SLOT(multiply()));
	connect(divideButton, SIGNAL(clicked()), this, SLOT(divide()));
}
void Calculator :: setSum(int sum) {
	this->sum = sum;
}
void Calculator :: plus() {
	QString str = QString :: number(sum);
	QString text = lineEdit->text();
	int number = text.toInt();
	sum = sum + number;
	lineEdit->clear();
	str.append(" + ");
	str.append(QString :: number(number));
	send(str);
}
void Calculator :: minus() {
	QString str = QString :: number(sum);
	QString text = lineEdit->text();
	int number = text.toInt();
	sum = sum - number;
	lineEdit->clear();
	str.append(" - ");
	str.append(QString :: number(number));
	send(str);
}
void Calculator :: multiply() {
	QString str = QString :: number(sum);
	QString text = lineEdit->text();
	int number = text.toInt();
	sum = sum * number;
	lineEdit->clear();
	str.append(" * ");
	str.append(QString :: number(number));
	send(str);
}
void Calculator :: divide() {
	QString str = QString :: number(sum);
	QString text = lineEdit->text();
	int number = text.toInt();
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
