#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QLabel>
#include <QTextEdit>
#include <QAction>

#include "CalcDialog.h"
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT;

    Ui::MainWindow ui;
    
    public:
        MainWindow(QWidget *parent = NULL);
        ~MainWindow();
        
    public:
        
    private: // UI elements
        CalcDialog* calcDialog;
        QLabel *lblFilename;
        QLabel *lblResult;

    private:
        QString logHistory;
        QString resultHistory;
		
    private:
        void createConnects();
        void loadSettings();
        void saveSettings();
        void setStatusBar();
    
    signals:
    
    public slots:
        void on_actOpenFile_triggered();
        void on_actSaveFile_triggered();
        void on_actRevertFile_triggered();
        void on_actShowCalc_triggered(bool checked);
        void exprCalculated(double oper1, char operation, double oper2, double result);
};


#endif
