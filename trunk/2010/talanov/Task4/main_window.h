#ifndef TASK4_H
#define TASK4_H

#include <QtGui/QMainWindow>
#include <QTGui/QStatusBar>
#include <QtGui/QLabel>
#include <QtGui/QAction>
#include <QtGui/QPlainTextEdit>

#include "calculator.h"

class CalculatorLogMW : public QMainWindow
{
   Q_OBJECT

public:
  CalculatorLogMW(QWidget *parent = 0, Qt::WFlags flags = 0);
  ~CalculatorLogMW();


public slots:

  void openFile();
  void openFile(const QString&);
  void saveFile();
  void saveFileAs();
  void revertFile();
  void calculator();
  void setResult(int);
  void addText(const QString&);

private:

  void setUpWidgets();
  void createActions();
  void setUpMenu();
  void setUpStatusBar();
  void connectToSlots();

  void setFilename(const QString&);

private:

  //
  QString myFilename;

  int myResult;

  //status bar labels
  QLabel* myStatusResultLabel;
  QLabel* myStatusLogFilenameLabel;

  //central widget
  QPlainTextEdit* myTextEdit;

  //calculator widget
  Calculator* myCalculator;

  //actions
  QAction* myOpenAction;
  QAction* mySaveAction;
  QAction* mySaveAsAction;
  QAction* myRevertAction;
  QAction* myCalculatorAction;

};

#endif // TASK4_H
