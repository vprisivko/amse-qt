#include "calculator.h"

#include <QtGui/QPushButton>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLineEdit>


Calculator::Calculator(QWidget *parent, Qt::WFlags flags)
: QDialog(parent, flags)
{

  myValue = 0;

  //create widgets

  QVBoxLayout *mainLayout = new QVBoxLayout();
  myLineEdit = new QLineEdit("0", this);
  mainLayout->addWidget(myLineEdit);

  QHBoxLayout *buttonLayout = new QHBoxLayout();
  QPushButton *addButton = new QPushButton("+", this);
  buttonLayout->addWidget(addButton);
  QPushButton *subButton = new QPushButton("-", this);
  buttonLayout->addWidget(subButton);
  QPushButton *multButton = new QPushButton("*", this);
  buttonLayout->addWidget(multButton);
  QPushButton *divButton = new QPushButton("/", this);
  buttonLayout->addWidget(divButton);

  mainLayout->addItem(buttonLayout);

  setLayout(mainLayout);

  //connect
  connect(addButton, SIGNAL(clicked()), this, SLOT(add()));
  connect(subButton, SIGNAL(clicked()), this, SLOT(subtract()));
  connect(multButton, SIGNAL(clicked()), this, SLOT(multiply()));
  connect(divButton, SIGNAL(clicked()), this, SLOT(divide()));
  connect(myLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(setValue(const QString&)));

  
}

Calculator::~Calculator()
{

}

void Calculator::setResult(int res)
{
  myResult = res;
  emit resultChanged(myResult);
}

void Calculator::setValue(const QString& value)
{
  bool success;
  int newValue = value.toInt(&success);
  if (!success)
  {
    myLineEdit->setText(QString::number(myValue));
  }
  myValue = newValue;
}

void Calculator::add()
{
  emit addText(QString::number(myResult) + " + " + QString::number(myValue) + " = " + QString::number(myResult + myValue));
  setResult(myResult + myValue);
}

void Calculator::subtract()
{
  emit addText(QString::number(myResult) + " - " + QString::number(myValue) + " = " + QString::number(myResult - myValue));
  setResult(myResult - myValue);
}

void Calculator::multiply()
{
  emit addText(QString::number(myResult) + " * " + QString::number(myValue) + " = " + QString::number(myResult * myValue));
  setResult(myResult * myValue);
}

void Calculator::divide()
{
  if (myValue == 0)
  {
    return;
  }
  emit addText(QString::number(myResult) + " / " + QString::number(myValue) + " = " + QString::number(myResult / myValue));
  setResult(myResult / myValue);
}

const int Calculator::result() const
{
  return myResult;
}
