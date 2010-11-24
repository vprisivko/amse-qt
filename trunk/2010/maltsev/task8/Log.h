#ifndef LOG_H
#define LOG_H

#include "Calculator.h"
#include <QMainWindow>
#include <QLabel>
#include <QTextEdit>
#include "ui_Log.h"

class Log: public QMainWindow {
Q_OBJECT;

public:
    Log(QWidget *w = 0);
    ~Log();
    double result;

private:
    Ui::MainWindow MW;
    bool opened;
    QLabel *logName, *lastResult;
    QString fileName;
    Calculator* c;

public slots:
    void Open();
    void Save();
    void Revert();
    void Calc();

};

#endif
