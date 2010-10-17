#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include<QMainWindow>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QObject>
#include<QStatusBar>
#include<QToolBar>
#include<QTextEdit>
#include<QLabel>
#include<QSettings>
#include"Calculator.h"
class MyMainWindow : public QMainWindow {
    Q_OBJECT;
public:

        QMenu *fileMenu;
        QMenu *toolMenu;
        QToolBar *toolBar;
        QLabel *nameLog;
        QLabel *resultLabel;
        QTextEdit *centralLog;
        QAction *open;
        QAction *save;
        QAction *revert;
        QAction *calculator;
        QString currentFile;
        Calculator *calcDialog;
        QString historyFile;
        QString fileResult;
        QSettings *settings;


        MyMainWindow();
        ~MyMainWindow();
        void createWidgets();
        void addWidgets();
        void connectWidgets();
public slots:
        void showCalc(bool vis);
        void writeCalcLine(QString str, double res);
        void openFile();
        void saveFile();
        void revertFile();
};
#endif // MYMAINWINDOW_H
