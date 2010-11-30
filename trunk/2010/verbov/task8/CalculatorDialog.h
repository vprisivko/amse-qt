#ifndef _CALCULATOR_DIALOG_H_
#define _CALCULATOR_DIALOG_H_

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>

class CalculatorDialog : public QDialog {

	Q_OBJECT

public:
	CalculatorDialog(QWidget *parent = 0);
	void createWidgets();
	void fillLayout();
	void connectSignalsAndSlots();
	void calculate(char operation);
	void setResult(double newResult);

signals:
	void addOperation(const QString &text);
	void resultChanged(double result);

public slots:
	void plus();
	void minus();
	void times();
	void divide();

private:
	QPushButton *plusButton, *minusButton, *timesButton, *divideButton;
	QLineEdit *inputLine;
	double result;
	char lastOperation;

};

#endif // _CALCULATOR_DIALOG_H_
