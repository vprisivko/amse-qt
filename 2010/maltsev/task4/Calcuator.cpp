#include "Calculator.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>

Calculator::Calculator(int* res, QLabel* lg, QLabel* r, bool* b, QWidget *parent): QDialog(parent) {
  presult = res;
  result = *presult;
  verynew = b;
  log = lg;
  reslb = r;
  stack = 0;
  setLayout(new QVBoxLayout());
  l = new QLineEdit(QString::number(result), this);
  l->setAlignment(Qt::AlignRight);
  layout()->addWidget(l);
  QHBoxLayout *hl = new QHBoxLayout();
  a = new QPushButton("+", this);
  s = new QPushButton("-", this);
  m = new QPushButton("*", this);
  d = new QPushButton("/", this);
  hl->addWidget(a);
  hl->addWidget(s);
  hl->addWidget(m);
  hl->addWidget(d);
  layout()->addItem(hl);
  connect(a, SIGNAL(clicked()), 
          this, SLOT(Add()) );
  connect(s, SIGNAL(clicked()), 
          this, SLOT(Sub()) );
  connect(m, SIGNAL(clicked()), 
          this, SLOT(Mul()) );
  connect(d, SIGNAL(clicked()), 
          this, SLOT(Div()) );
}

void Calculator::Process() {
  int arg = l->text().toInt();
  l->setText("0");
  l->setReadOnly(false);
  if (stack == 0) {
    result = arg;
    return;
  }
  *verynew = false;
  if (stack == '+') {
    log->setText(log->text() + QString::number(result) + " + " + QString::number(arg) + " = " + QString::number(result + arg) + "\n");
    *presult = result + arg;
    result = *presult;
    reslb->setText(QString::number(result));
  }
  if (stack == '-') {
    log->setText(log->text() + QString::number(result) + " - " + QString::number(arg) + " = " + QString::number(result - arg) + "\n");
    *presult = result - arg;
    result = *presult;
    reslb->setText(QString::number(result));
  }
  if (stack == '*') {
    log->setText(log->text() + QString::number(result) + " * " + QString::number(arg) + " = " + QString::number(result * arg) + "\n");
    *presult = result * arg;
    result = *presult;
    reslb->setText(QString::number(result));
  }
  if (stack == '/') {
    log->setText(log->text() + QString::number(result) + " / " + QString::number(arg) + " = " + QString::number(result / arg) + "\n");
    *presult = result / arg;
    result = *presult;
    reslb->setText(QString::number(result));
  }
}

void Calculator::Reload(int * r) {
  stack = 0;
  presult = r;
  result = *presult;
  l->setText(QString::number(result));
  l->setReadOnly(true);
  stack = 0;
}

void Calculator::Add() {
  Process();
  stack = '+';
}

void Calculator::Sub() {
  Process();
  stack = '-';
}

void Calculator::Mul() {
  Process();
  stack = '*';
}

void Calculator::Div() {
  Process();
  stack = '/';
}
