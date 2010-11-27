#ifndef CALCCREATOR_H
#define CALCCREATOR_H

#include <QtGui/QWidget>
#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QLabel>
#include <QFileDialog>

#include <QtGui/QMainWindow>
#include "ui_calccreator.h"
#include "calcdockwgt.h"

class CalcCreator : public QMainWindow
{
    Q_OBJECT

    QLabel * m_logName;
    QLabel * m_lastResult;

    CalcDockWgt * m_calculator;
    QString m_fileName;

public:
    CalcCreator(QWidget *parent = 0);
    ~CalcCreator(){}

private:
    Ui::CalcCreatorClass ui;

	void createStatusBar();
	void createDockWidget();
	void connectEvents();

public slots:
	void save();
	void open();
	void revert();
	void writeLog(double, double, double, char) const;
};

#endif // CALCCREATOR_H


