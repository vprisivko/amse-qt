#ifndef LOG_H
#define LOG_H

#include "Calculator.h"
#include <QMainWindow>
#include <QLabel>

class Log: public QMainWindow {
Q_OBJECT;

public:
  Log(QWidget *w = 0);
  ~Log();
  int result;

private:
  bool opened;
  QLabel* l, *logName, *lastResult;
  QString fileName;
  Calculator* c;
  bool isEmpty;

public slots:
  void Open();
  void Save();
  void Revert();
  void Calc();

};

#endif
