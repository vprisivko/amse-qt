#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "Calculator.h"
#include <QMainWindow>
#include <QLabel>
#include <QTextEdit>

class MainWindow : public QMainWindow {
    Q_OBJECT;

public:
    MainWindow(QWidget *parent = NULL);

private:
    Calculator* calc;
    QString logHistory;
    QString lastResultHistory;
    QLabel *filenameLabel;
    QLabel *lastResultLabel;
    QTextEdit* logTextEdit;

public slots:
    void addToLog(QString str, double res);
    void openFile();
    void saveFile();
    void revertFile();
    void showCalculator(bool isChecked);
};

#endif
