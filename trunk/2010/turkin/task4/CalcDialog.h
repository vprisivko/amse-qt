#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>

 
class CalcDialog : public QDialog {
    Q_OBJECT;
    
    public:
        CalcDialog(QWidget *parent = NULL);
        void setResult(double);
    public:
        void hideEvent( QHideEvent* event );
    private:
        void makeOperation( char op );
    private: // UI elements
        QLineEdit* leDigits;
        QPushButton* btnPlus;
        QPushButton* btnMinus;
        QPushButton* btnMultiply;
        QPushButton* btnDivide;		
    private:
        void createDigits();
        void createButtons();
        void createConnects();
    private:
        double myResult;
    signals:
        void expr(double oper1, char operation, double oper2, double result);
    	void calcHide(bool);
    public slots:
        void plus();
        void minus();
        void multiply();
        void divide();

};


#endif
