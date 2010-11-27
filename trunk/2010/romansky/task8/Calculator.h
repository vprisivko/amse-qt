#ifndef CALCULATOR_H
#define CALCULATOR_H


#include <QPoint>
#include <QRect>
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <QColor>
#include <QFont>
#include <QMainWindow>
#include <QInputDialog>
#include <QString>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QAction>
#include <QLineEdit>
#include <QStatusBar>
#include <QLabel>
#include <QCloseEvent>
#include <QVector>
#include <QFile>
#include <Qt>
#include <QSettings>
#include <QBoxLayout>
#include <QFileDialog>
#include <QIODevice>
#include <QMessageBox>

#include "ui_Calculator.h"

class Calculator:public QMainWindow{
  Q_OBJECT;
  
  QDialog* mycalc;
  Ui::MainWindow MW;

  double mycurrentresult;
  double myoperand;
  char myoperation;
  QLabel* mylogname;
  QLabel* mylabelresult;
  QVector<QLabel*> myoperations; 
  
  QLineEdit* myinputline;
  QDialog* mycalculationdialog;
  QFile* mylog;
  int mylogstringcount;
  double mylogresult;
  QMessageBox* mymessage;
  
  public:
  Calculator(QWidget* p = 0);
  ~Calculator();

  public slots:
  void Add();
  void Sub();
  void Mul();
  void Div();
  void Calc();
  void Open();
  void Save();
  void Revert();
};


#endif
