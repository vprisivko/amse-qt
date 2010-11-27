#include "calcdockwgt.h"

CalcDockWgt::CalcDockWgt(QWidget *parent)
    : QWidget(parent), m_firstOperand(NULL)
{
	createItems();
	puttItemsOnTheForm();
	connectAllTheStuff();
}

void CalcDockWgt::createItems(){
    m_input = new QLineEdit(this);
    m_input->setValidator(new QDoubleValidator());

    m_butMultiply = new QPushButton("*", this);
    m_butDivide = new QPushButton("/", this);
    m_butPlus = new QPushButton("+", this);
    m_butMinus = new QPushButton("-", this);

    m_butMultiply->setFixedSize(40,25);
    m_butDivide->setFixedSize(40,25);
    m_butPlus->setFixedSize(40,25);
    m_butMinus->setFixedSize(40,25);
}

void CalcDockWgt::puttItemsOnTheForm(){
	QVBoxLayout * calcLayout = new QVBoxLayout(this);
	QHBoxLayout * buttonLayout = new QHBoxLayout();

	buttonLayout->addWidget(m_butMultiply);
	buttonLayout->addWidget(m_butDivide);
	buttonLayout->addWidget(m_butPlus);
	buttonLayout->addWidget(m_butMinus);

	calcLayout->addWidget(m_input);
	calcLayout->addItem(buttonLayout);
	calcLayout->addStretch();
}

void CalcDockWgt::connectAllTheStuff(){
	QObject::connect(m_butMultiply, SIGNAL(clicked ()), this, SLOT(multiply()));
	QObject::connect(m_butDivide, SIGNAL(clicked ()), this, SLOT(divide()));
	QObject::connect(m_butMinus, SIGNAL(clicked ()), this, SLOT(substract()));
    QObject::connect(m_butPlus, SIGNAL(clicked ()), this, SLOT(add()));
}

void CalcDockWgt::add(){
	m_secondOperand = m_input->text().toDouble();
	emit plus_signal(m_firstOperand + m_secondOperand, m_secondOperand, m_firstOperand, '+');
	m_firstOperand += m_secondOperand;
	m_input->clear();
}

void CalcDockWgt::substract(){
	m_secondOperand = m_input->text().toDouble();
	emit minus_signal(m_firstOperand - m_secondOperand, m_secondOperand, m_firstOperand, '-');
	m_firstOperand -= m_secondOperand;
	m_input->clear();
}

void CalcDockWgt::multiply(){
	m_secondOperand = m_input->text().toDouble();
	emit multiply_signal(m_firstOperand * m_secondOperand, m_secondOperand, m_firstOperand, '*');
	m_firstOperand *= m_secondOperand;
	m_input->clear();
}

void CalcDockWgt::divide(){
	m_secondOperand = m_input->text().toDouble();

	if(m_secondOperand == 0){
		QErrorMessage * nullDivisionError = new QErrorMessage(this);
		nullDivisionError->setWindowTitle("Warning!");
		nullDivisionError->showMessage("Don't try to divide on zero!");
		return;
	}

	emit divide_signal(m_firstOperand / m_secondOperand, m_secondOperand, m_firstOperand, '/');
	m_firstOperand /= m_secondOperand;
	m_input->clear();
}

void CalcDockWgt::setLastResult(double result){
	m_firstOperand = result;
}
