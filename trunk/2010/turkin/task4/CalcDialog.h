#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QPushButton>
#include <QLineEdit>

 
class CalcDialog : public QDialog {
    Q_OBJECT;
    
    public:
        CalcDialog(QWidget *parent = NULL);
        void setResult(int);
    public:
    
	private: 
		void makeOperation( char op );	
    private: // UI elements
        QLineEdit* leDigits;
        QPushButton* btnPlus;
        QPushButton* btnMinus;
		QPushButton* btnMultiply;
		QPushButton* btnDivide;
    

    private:
		int curResult;
		char curOperation;
    
    
	signals:
    	void expr(QString string, int result);
    public slots:
		void plus();
		void minus();
		void multiply();
		void divide();

};


#endif
