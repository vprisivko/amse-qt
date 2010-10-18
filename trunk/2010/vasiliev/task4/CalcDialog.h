#ifndef _CALC_DIALOG_H_
#define _CALC_DIALOG_H_

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

class CalcDialog: public QDialog {

Q_OBJECT;

public:
	CalcDialog(QWidget *parent = NULL);
	void setResult(int result);
	int getResult() const;

public slots:
	void add();
	void sub();
	void mul();
	void div();

signals:
	void sendExpression(QString, int);

private:
	void doArythmethic(const char &operation);

private:
	int myResult;
	QPushButton *myPlusBtn;
	QPushButton *myMinusBtn;
	QPushButton *myMultiplyBtn;
	QPushButton *myDivisionBtn;

	QLineEdit *myExpressionEdit;

};

#endif // _CALC_DIALOG_H_
