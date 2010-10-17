#ifndef CALCDOCKWGT_H
#define CALCDOCKWGT_H

#include <QtGui/QWidget>
#include <QDockWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

class CalcDockWgt : public QWidget
{
    Q_OBJECT

    int m_firstOperand;
    int m_secondOperand;

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
	void plus_signal(int, int, int, char);
	void minus_signal(int, int, int, char);
	void multiply_signal(int, int, int, char);
	void divide_signal(int, int, int, char);

public:
    CalcDockWgt(QWidget *parent = 0);
    ~CalcDockWgt() {}

    void setLastResult(int);

private:
	void createItems();
	void puttItemsOnTheForm();
	void connectAllTheStuff();
};

#endif // CALCDOCKWGT_H
