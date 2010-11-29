#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QString>

class Calculator : public QDialog {
    Q_OBJECT;

public:
    Calculator(QWidget *parent = NULL);

private:
    void calculate(char str);

private:
    QPushButton *plusButton;
    QPushButton *minusButton;
    QPushButton *asterixButton;
    QPushButton *slashButton;
    QLineEdit *numberLineEdit;

signals:
    void toWrite(QString str, double res);

public slots:
    void sumUp();
    void subtract();
    void multiply();
    void divide();

public:
    double myCurResult;
};

#endif
