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
    void setCurrentValue(int value);

signals:
    void newString(QString logString, int result);

private slots:
    void plusSlot();
    void minusSlot();
    void mulSlot();
    void divSlot();

private:
    void createDialog();
    void sendString(int arg1, int arg2, char operation);
    void closeCurrentFile();

    int currentValue;

    QPushButton* plusButton;
    QPushButton* minusButton;
    QPushButton* divButton;
    QPushButton* mulButton;
    QLineEdit* numLine;
};

#endif // CALCDIALOG_H
