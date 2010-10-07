#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class Calculator: public QDialog {
Q_OBJECT;

public:
  Calculator(int*, QLabel*, QLabel*, bool*, QWidget *w = 0);
  int *presult;
  int result;
  QLabel* log;
  QLabel* reslb;
  bool * verynew;
  QChar stack;
  void Process();
  void Reload(int *);

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
