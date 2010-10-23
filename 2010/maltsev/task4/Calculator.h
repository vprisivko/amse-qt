#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>

class Calculator: public QDialog {
Q_OBJECT;

public:
  Calculator(double*, QTextEdit*, QLabel*, QWidget *w = 0);
  double *presult;
  double result;
  QTextEdit* log;
  QLabel* reslb;
  void Reload(double *);

private:
  QLineEdit* l;
  QPushButton *a, *s, *m, *d;

public slots:
  void Add();
  void Sub();
  void Mul();
  void Div();

};

#endif
