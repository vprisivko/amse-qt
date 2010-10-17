#ifndef CALCLOG_H
#define CALCLOG_H

#include <QtGui/QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <QAction>
#include <QStatusBar>
#include <QTextEdit>
#include <QLabel>
#include <QFile>
#include <QTextStream>

#include "calcdialog.h"

class CalcLog : public QMainWindow
{
    Q_OBJECT;

public:
    CalcLog(QWidget *parent = 0);
    ~CalcLog();

public slots:
    void addString(QString logString, int result);

private slots:
    void openFileSlot();
    void saveCurrentFileSlot();
    void saveFileSlot();
    void revertSlot();
    void showCalcDialogSlot();

private:
    void createMenuBar();
    void createWindow();
    void connectSlots();

    void updateStatusBar();
    void saveToFile( QString fileName );
    void loadFromFile( QString fileName );

    CalcDialog* calcDialog;

    QAction* saveFileAction;
    QAction* saveCurrentFileAction;
    QAction* openFileAction;
    QAction* revertAction;
    QAction* showCalcAction;

    QTextEdit* calcLog;

    QLabel* fileNameLabel;
    QLabel* lastResultLabel;

    QString currentFileName;

    //QFileDialog* fileDialog;
    //QFile* currentFile;
    //QTextStream* currentStream;

    int lastResult;
};

#endif // CALCLOG_H
