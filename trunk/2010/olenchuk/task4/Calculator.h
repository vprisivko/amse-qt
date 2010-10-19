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
		void setSum(int sum);
	
	signals:
		void answer(QString str);	
	
	private slots:
		void plus();
		void minus();
		void multiply();
		void divide();
	private:
		void send(QString &str);

	
	private:
		int sum;
		QString str;
		QLineEdit *lineEdit;
		QPushButton *plusButton;
		QPushButton *minusButton;
		QPushButton *divideButton;
		QPushButton *multiplyButton;
};

#endif
