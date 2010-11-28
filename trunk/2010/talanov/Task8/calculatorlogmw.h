#ifndef CALCULATORLOGMW_H
#define CALCULATORLOGMW_H

#include <QMainWindow>

#include <QtGui/QLabel>

#include "calculator.h"

namespace Ui {
    class CalculatorLogMW;
}

class CalculatorLogMW : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalculatorLogMW(QWidget *parent = 0);
    ~CalculatorLogMW();

public slots:

  void openFile();
  void openFile(const QString&);
  void saveFile();
  void saveFileAs();
  void revertFile();
  void calculator();

  void setResult(qreal);
  void addText(const QString& text);

private:

  void setUpStatusBar();
  void connectToSlots();
  void setFilename(const QString&);

private:
    Ui::CalculatorLogMW *ui;

    //status bar labels
    QLabel* myStatusResultLabel;
    QLabel* myStatusLogFilenameLabel;

    QString myFilename;
    qreal myResult;
    //calculator widget
    Calculator* myCalculator;
};

#endif // CALCULATORLOGMW_H
