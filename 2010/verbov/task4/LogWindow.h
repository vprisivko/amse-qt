#ifndef _LOG_WINDOW_H_
#define _LOG_WINDOW_H_

#include <QMainWindow>
#include <QAction>
#include <QTextEdit>
#include <QLabel>
#include "CalculatorDialog.h"

class LogWindow : public QMainWindow {

	Q_OBJECT;

public:
	LogWindow(QWidget *parent = 0);
	void createActions();
	void createMenu();
	void createStatusBar();
	void createCentralWidget();
	void connectSignalsAndSlots();

public slots:
	void fileOpen();
	void fileSave();
	void revert();
	void runCalculator();
	void updateResult(double result);

private:
	void readFile();

private:
	QAction *openAction, *saveAction, *revertAction, *calculatorAction;
	QTextEdit *logText;
	QLabel *filenameLabel, *resultLabel;
	CalculatorDialog *calculator;
	QString filename;
	double lastResult;

};

#endif //_LOG_WINDOW_H_
