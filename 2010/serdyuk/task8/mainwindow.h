// =====================================================================================
// 
//       Filename:  mainwindow.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  14.10.2010 12:18:42
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT;
public:
    MainWindow(QWidget *p = 0);

    void closeEvent(QCloseEvent *);

private:
    Ui::MainWindow *ui;

    QLabel *myLogName;
    QLabel *myOperationResult;

    QWidget *myCalculator;
    QLineEdit *myCalcEdit;
    QPushButton *myPlusButton;
    QPushButton *mySubsButton;
    QPushButton *myMultButton;
    QPushButton *myDivButton;

    double lastResult;

    QString previousLog;
    QString previousResult;

    void createStatusBar();
    void createCalc();
    void createConnections();
    void createToolBar();

    void changeLastResult(char operation);

    void writeSettings();
    void readSettings();

public slots:
    void add();
    void substrate();
    void multiply();
    void divide();

private slots:
    void on_actionToggle_calculator_triggered();
    void on_action_Revert_triggered();
    void on_action_Save_triggered();
    void on_action_Open_triggered();
};

#endif   // ----- #ifndef MAINWINDOW_H -----

