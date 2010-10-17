#include <QDoubleValidator>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "calcdialog.h"


CalcDialog::CalcDialog(QWidget *parent /* = 0 */) : QDialog(parent)
{
	setWindowTitle("Calculator");

	QVBoxLayout *lay = new QVBoxLayout(this);
	input_ = new QLineEdit(this);
	QDoubleValidator *validator = new QDoubleValidator(input_);
	input_->setValidator(validator);
	lay->addWidget(input_);

	QHBoxLayout *lay2 = new QHBoxLayout();
	QPushButton *btnPlus = new QPushButton("+", this);
	QPushButton *btnMinus = new QPushButton("-", this);
	QPushButton *btnMultiply = new QPushButton("*", this);
	QPushButton *btnDivide = new QPushButton("/", this);
	lay2->addWidget(btnPlus);
	lay2->addWidget(btnMinus);
	lay2->addWidget(btnMultiply);
	lay2->addWidget(btnDivide);
	lay->addLayout(lay2);

	connect(btnPlus, SIGNAL(clicked()), SLOT(plus_click()));
	connect(btnMinus, SIGNAL(clicked()), SLOT(minus_click()));
	connect(btnMultiply, SIGNAL(clicked()), SLOT(multiply_click()));
	connect(btnDivide, SIGNAL(clicked()), SLOT(divide_click()));

	connect(btnPlus, SIGNAL(clicked()), input_, SLOT(setFocus()));
	connect(btnMinus, SIGNAL(clicked()), input_, SLOT(setFocus()));
	connect(btnMultiply, SIGNAL(clicked()), input_, SLOT(setFocus()));
	connect(btnDivide, SIGNAL(clicked()), input_, SLOT(setFocus()));
}

double CalcDialog::getLastResult() const
{
	return lastResult_;
}

void CalcDialog::setLastResult(double value)
{
	lastResult_ = value;
	input_->setText(QString::number(lastResult_));
}

void CalcDialog::calculate(double value, QString op)
{
	QString expr = QString::number(getLastResult()).append(" ");
	expr = expr.append(op).append(" ").append(input_->text());
	expr = expr.append(" = ").append(QString::number(value));
	emit evaluated(expr, value);
	lastResult_ = value;
}

void CalcDialog::plus_click()
{
	calculate(lastResult_+ input_->text().toDouble(), "+");
}

void CalcDialog::minus_click()
{
	calculate(lastResult_ - input_->text().toDouble(), "-");
}

void CalcDialog::multiply_click()
{
	calculate(lastResult_ * input_->text().toDouble(), "*");
}

void CalcDialog::divide_click()
{
	calculate(lastResult_ / input_->text().toDouble(), "/");
}
