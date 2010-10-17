#ifndef _CALCDIALOG_H_
#define _CALCDIALOG_H_

#include <QDialog>
#include <QLineEdit>


class CalcDialog : public QDialog
{
	Q_OBJECT;

public:
	CalcDialog(QWidget *parent = 0);

	double getLastResult() const;
	void setLastResult(double value);

private:
	void calculate(double value, QString op);

signals:
	void evaluated(QString expr, double result);

private slots:
	void plus_click();
	void minus_click();
	void multiply_click();
	void divide_click();

private:
	QLineEdit *input_;
	double lastResult_;
};

#endif