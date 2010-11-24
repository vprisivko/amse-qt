#include "Calculator.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QMessageBox>

Calculator::Calculator(double* res, QTextEdit* lg, QLabel* r, QWidget *parent): QDialog(parent) {
  presult = res;
  result = *presult;
  log = lg;
  reslb = r;
  setLayout(new QVBoxLayout());
  l = new QLineEdit("0", this);
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

void Calculator::Reload(double *) {
  result = *presult;
}

void Calculator::Add() {
  double arg = l->text().toDouble();
  log->append(QString::number(result) + " + " + QString::number(arg) + " = " + QString::number(result + arg));
    *presult = result + arg;
    result = *presult;
    reslb->setText(QString::number(result));
}

void Calculator::Sub() {
  double arg = l->text().toDouble();
  log->append(QString::number(result) + " - " + QString::number(arg) + " = " + QString::number(result - arg));
    *presult = result - arg;
    result = *presult;
    reslb->setText(QString::number(result));
}

void Calculator::Mul() {
  double arg = l->text().toDouble();
  log->append(QString::number(result) + " * " + QString::number(arg) + " = " + QString::number(result * arg));
    *presult = result * arg;
    result = *presult;
    reslb->setText(QString::number(result));
}

void Calculator::Div() {
  double arg = l->text().toDouble();
  if (arg == 0) {
    QMessageBox zeroBox;
    zeroBox.setText("Please, do not divide by zero.");
    zeroBox.exec();
    return;
  }
  log->append(QString::number(result) + " / " + QString::number(arg) + " = " + QString::number(result / arg));
    *presult = result / arg;
    result = *presult;
    reslb->setText(QString::number(result));
}
