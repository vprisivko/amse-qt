#ifndef CALCULATOR_H
#define CALCULATOR_H
#include<QDialog>
#include<QPushButton>
#include<QString>
#include<QLineEdit>
class Calculator:public QDialog {
    Q_OBJECT;
public:
        double result;
        char op;
        QPushButton *plus;
        QPushButton *minus;
        QPushButton *times;
        QPushButton *divide;
        QLineEdit *inputLine;


        Calculator(double res,QWidget *parent);
        void createButtons();
        void addButtons();
        void connectButtons();
        void makeOperation(char c);
signals:
        void newexpr(QString str, double res);
public slots:
        void plusOp();
        void minusOp();
        void multOp();
        void divOp();




};
#endif // CALCULATOR_H
