#ifndef CALCDIALOG_H
#define CALCDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>

class CalcDialog : public QDialog
{
Q_OBJECT;

public:
    CalcDialog(QWidget *parent = 0);
    void setCurrentValue(double value);

signals:
    void newString(QString logString, double result);
    void dialogClosed();

private slots:
    void plusSlot();
    void minusSlot();
    void mulSlot();
    void divSlot();

private:
    void createDialog();
    void sendString(double arg1, double arg2, char operation);
    void closeCurrentFile();
    void closeEvent(QCloseEvent*);

    double currentValue;

    QPushButton* plusButton;
    QPushButton* minusButton;
    QPushButton* divButton;
    QPushButton* mulButton;
    QLineEdit* numLine;
};

#endif // CALCDIALOG_H
