#ifndef CALCDOCKWGT_H
#define CALCDOCKWGT_H

#include <QtGui/QWidget>
#include <QDockWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QErrorMessage>
#include <QDoubleValidator>

class CalcDockWgt : public QWidget
{
    Q_OBJECT

    double m_firstOperand;
    double m_secondOperand;

    QLineEdit * m_input;
    QPushButton * m_butMultiply;
    QPushButton * m_butDivide;
    QPushButton * m_butPlus;
    QPushButton * m_butMinus;
    QPushButton * m_butEquals;

public slots:
	void multiply();
	void divide();
	void substract();
	void add();

signals:
	void plus_signal(double, double, double, char);
	void minus_signal(double, double, double, char);
	void multiply_signal(double, double, double, char);
	void divide_signal(double, double, double, char);

public:
    CalcDockWgt(QWidget *parent = 0);

    void setLastResult(double);

private:
	void createItems();
	void puttItemsOnTheForm();
	void connectAllTheStuff();
};

#endif // CALCDOCKWGT_H
