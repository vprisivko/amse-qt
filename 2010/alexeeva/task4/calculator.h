#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QtGui/QWidget>
#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QLabel>
#include <QFileDialog>

#include "calcdockwgt.h"

class Calculator : public QMainWindow
{
    Q_OBJECT

    QAction * m_save;
    QAction * m_open;
    QAction * m_revert;
    QAction * m_openCalcWidget;

    QMenu * m_fileMenu;

    QToolBar * m_toolbar;
    QToolBar * m_toolbarCalc;

    QTextEdit * m_edit;

    QLabel * m_logName;
    QLabel * m_lastResult;

    CalcDockWgt * m_calculator;
    QDockWidget * m_dockWgt;

    QString m_fileName;

public:
    Calculator(QWidget *parent = 0);
    ~Calculator() {}

private:
	void createActions();
	void initMainWindow();
	void createMenuBar();
	void createToolBars();
	void createStatusBar();
	void createDockWidget();
	void connectEvents();

public slots:
	void save();
	void open();
	void revert();
	void writeLog(int, int, int, char);
};
#endif //CALCULATOR_H
