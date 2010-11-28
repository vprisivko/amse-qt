#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QToolBar>
#include <QMenu>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QLineEdit>

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);

private:
	Ui::MainWindow ui;
	 void createConnections();
	 void createStatusBar();
	 void createDockCalculator();
	 void loadFile(const QString &fileName);
	 bool saveFile(const QString &fileName);

private slots:
	void open();
	bool save();
	void revert();
	void documentWasModified();

	void plusPressed();
	void minusPressed();
	void multPressed();
	void dividePressed();

private:
	 double myResult;
	 QString curFile;

	 QStatusBar *myStatusBar;
	 QLabel *logNameLabel;
	 QLabel *logName;
	 QLabel *lastResultLabel;
	 QLabel *lastResult;
	 QDialog *myCalculator;
	 QPushButton *plusButton;
	 QPushButton *minusButton;
	 QPushButton *multButton;
	 QPushButton *divideButton;
	 QLineEdit *myInput;

	 QDockWidget *dock;
};

#endif // MAINWINDOW_H
