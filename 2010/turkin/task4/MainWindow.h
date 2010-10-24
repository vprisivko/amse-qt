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

class MainWindow : public QMainWindow {
    Q_OBJECT;
    
    public:
        MainWindow(QWidget *parent = NULL);
        ~MainWindow();
        
    public:
        
    private: // UI elements
        CalcDialog* calcDialog;
        QTextEdit* teLog;
        QLabel *lblFilename;
        QLabel *lblResult;
        QString logHistory;
        QString resultHistory;
		
	private: //actions
        QAction* actOpenFile;
        QAction* actSaveFile;
        QAction* actRevertFile;
        QAction* actShowCalc;

    private:
        void createConnects();
        void loadSettings();
        void saveSettings();
        void createActions();
        void createToolBar();
        void createMenu();
        void createStatusBar();
        void createCentralWidget();
    
    signals:
    
    public slots:
        void slotOpenFile();
        void slotSaveFile();
        void slotRevertFile();
        void slotShowCalc(bool checked);
        void exprCalculated(double oper1, char operation, double oper2, double result);
};


#endif
