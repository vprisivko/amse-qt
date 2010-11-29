#ifndef _LOG_WINDOW_H_
#define _LOG_WINDOW_H_

#include <QMainWindow>
#include <QAction>
#include <QTextEdit>
#include <QDockWidget>
#include <QString>
#include <QLabel>

#include "Calculator.h"
#include "ui_LogWindow.h"

class LogWindow: public QMainWindow{
	Q_OBJECT;
  
public:
    	LogWindow( QWidget* parent = NULL );

private:
        void createLabels();
        void createStatusBar();
        void setConnection();

public slots:
    	void showCalc();
	void outputCalculation( QString expression, double result );
    	void fileOpen();
    	void fileSave();
    	void fileRevert();

private:
        Ui :: MainWindow logWindowUi;
    	QLabel* nameLabel;
    	QLabel* resultLabel;    	
    	QString fileName;
	Calculator* myCalcDialog;
};

#endif
