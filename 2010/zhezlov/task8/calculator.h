#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include "ui_calculator.h"
#include "ui_inputform.h"
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QLineEdit>
#include <QMessageBox>
#include "inputform.h"

namespace Ui {
    class Calculator;
}

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();

public slots:
    void updateText();
    void open();
    void save();
    void saveAs();
    void revert();
    void toggleForm();
    void reset();

private:
    Ui::Calculator *ui;
    InputForm* inputForm;
    QLabel* lastValueLabel;
    QLabel* fileNameLabel;
    QString fileName;
    double lastValue;

};

#endif // CALCULATOR_H
