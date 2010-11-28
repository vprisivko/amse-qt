#ifndef CALCULATOR_H
#define CALCULATOR_H


#include "QDialog"
#include "QLabel"
#include "QLineEdit"

class Calculator : public QDialog
{
    Q_OBJECT

public:
    double lastValue;

private:
    QLineEdit *lineEdit;

private:
    void createCalculator();

public:
    Calculator(QWidget *parent = NULL);

public slots:
    void calcButtonPressed();

signals:
    void exprCalc(QString str);


};

#endif // CALCULATOR_H
