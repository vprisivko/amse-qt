#ifndef _LOG_WINDOW_H_
#define _LOG_WINDOW_H_

#include "Calculator.h"
#include <QMainWindow>
#include <QAction>
#include <QTextEdit>
#include <QDockWidget>
#include <QString>
#include <QLabel>

class LogWindow: public QMainWindow{
	Q_OBJECT;
  
public:
    	LogWindow( QWidget* parent = NULL );
    
private:
    	void setConnection();
    	void createActions();  
    	void createMenu();
    	void createCentralText();
    	void createStatusBar();

public slots:
    	void showCalc();
	void outputCalculation( QString expression, double result );
    	void fileOpen();
    	void fileSave();
    	void fileRevert();

private:
    	QTextEdit* centralText;
    	QLabel* nameLabel;
    	QLabel* resultLabel;    	
    	QAction* openAction;
    	QAction* saveAction;
    	QAction* revertAction;
    	QAction* calculateAction;    	
    	QString fileName;
	Calculator* myCalcDialog;
};

#endif
