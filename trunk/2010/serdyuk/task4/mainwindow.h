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

class MainWindow : public QMainWindow {
    Q_OBJECT;
public:
    MainWindow(QWidget *p = 0);

    void closeEvent(QCloseEvent *);

private:
    QTextEdit *myTextEdit;

    QAction *mySaveAction;
    QAction *myOpenAction;
    QAction *myRevertAction;
    QAction *myCalculatorAciton;

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

    void createActions();
    void createStatusBar();
    void createMenuBar();
    void createCentralWidget();
    void createCalc();
    void createConnections();
    void createToolBar();

    void changeLastResult(char operation);

    void writeSettings();
    void readSettings();

public slots:
    void toggleCalculator();
    void add();
    void substrate();
    void multiply();
    void divide();
    void save();
    void open();
    void revert();
};

#endif   // ----- #ifndef MAINWINDOW_H -----

