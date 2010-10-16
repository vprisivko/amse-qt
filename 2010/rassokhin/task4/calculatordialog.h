#ifndef CALCULATORDIALOG_H
#define CALCULATORDIALOG_H

#include <QDialog>
#include <QLineEdit>

class CalculatorDialog : public QDialog {
    Q_OBJECT;
public:
    CalculatorDialog(QWidget * parent);

public:
    void setLastOpResult(qreal lr);

signals:
    void calculated(QString str, qreal value);

private:
    qreal lastResult;
    qreal operand;
    void getop();


    QLineEdit * numberInput;

    void processResult(qreal newValue, QString opSymbol);

private slots:
    void plus();
    void minus();
    void multiply();
    void divide();
};

#endif // CALCULATORDIALOG_H
