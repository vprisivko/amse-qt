#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class Calculator: public QDialog{
	Q_OBJECT;
  
public:
	Calculator( QWidget* parent = NULL );
    	void calcOperation( char operation );                
private:
	void initMembers();
	void createLineEdit();
	void createButtons();
        void addButtons();
        void connectButtons();

private slots:
    	void add();
    	void subtract();
    	void multiply();
    	void divide();
    
signals:
	void newExpr( QString str, double result );

public:
	double curResult;
    	
private:
    	QLineEdit* myLineEdt;
    	QPushButton* myAddBtn;
    	QPushButton* mySubtrBtn;
    	QPushButton* myMultBtn;
    	QPushButton* myDivBtn;

};

#endif
