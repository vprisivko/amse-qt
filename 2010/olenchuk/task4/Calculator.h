#ifndef H_CALCULATOR
#define H_CALCULATOR

#include <QDialog>

class QLineEdit;
class QPushButton;

 
class Calculator : public QDialog {
	Q_OBJECT;
    
	public:
		Calculator(QWidget *parent = 0);
		
	public:
		void setSum(double sum);
	
	signals:
		void answer(QString str);	
	
	private slots:
		void enableButton(const QString &text);
		void plus();
		void minus();
		void multiply();
		void divide();
	private:
		void send(QString &str);

	
	private:
		double sum;
		QString str;
		QLineEdit *lineEdit;
		QPushButton *plusButton;
		QPushButton *minusButton;
		QPushButton *divideButton;
		QPushButton *multiplyButton;
};

#endif
