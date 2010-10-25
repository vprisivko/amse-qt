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

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);

private:
	 void createActions();
	 void createConnections();
	 void createMenu();
	 void createCentralWidget();
	 void createToolBar();
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

	 QMenu *myMenu;
	 QMenu *myToolsMenu;
	 QStatusBar *myStatusBar;
	 QAction *openAction;
	 QAction *saveAction;
	 QAction *revertAction;
	 QAction *calcActoin;

	 QLabel *logNameLabel;
	 QLabel *logName;
	 QLabel *lastResultLabel;
	 QLabel *lastResult;
	 QPlainTextEdit *myTextEdit;
	 QDialog *myCalculator;
	 QPushButton *plusButton;
	 QPushButton *minusButton;
	 QPushButton *multButton;
	 QPushButton *divideButton;
	 QLineEdit *myInput;

	 QDockWidget *dock;
};

#endif // MAINWINDOW_H
