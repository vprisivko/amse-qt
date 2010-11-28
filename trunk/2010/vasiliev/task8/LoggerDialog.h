#ifndef _CALCULATION_LOG_H_
#define _CALCULATION_LOG_H_

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QAction>
#include <QLabel>
#include <QTextEdit>

#include "CalcDialog.h"
#include "ui_LoggerDialog.h"

class CalcLog: public QMainWindow {

Q_OBJECT;

public:
	CalcLog(QWidget *parent = NULL);

public slots:
	void openFile();
	void saveFile();
	void revertFile();
	void exit();
	void calc();

	void recieveExpression(QString, int);

private:

	Ui::MainWindow MW;
	//QAction *myOpenFileAction;
	//QAction *mySaveFileAction;
	//QAction *myRevertFileAction;
	//QAction *myCalcAction;
	//QAction *myExitAction;
	QLabel *myResultLabel;
	QLabel *myFileNameLabel;
	//QTextEdit *myProcessEdit;
	CalcDialog *myCalcDialog;
	QString myLogHistory;
	QString myLogResult;

};

#endif // _CALCULATION_LOG_H_
