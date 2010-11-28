#ifndef CALCLOG_H
#define CALCLOG_H

#include <QMainWindow>
#include <QLabel>
#include <QFile>
#include <QTextStream>

#include "calcdialog.h"

namespace Ui {
    class CalcLog;
}

class CalcLog : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalcLog(QWidget *parent = 0);
    ~CalcLog();

public slots:
    void addString(QString logString, double result);

private slots:
    void caclClosed();
    void openFileSlot();
    void saveCurrentFileSlot();
    void saveFileSlot();
    void revertSlot();
    void showCalcDialogSlot();

private:
    void connectSlots();

    void updateStatusBar();
    void saveToFile( QString fileName );
    void loadFromFile( QString fileName );

    CalcDialog* calcDialog;
    QString currentFileName;

    double lastResult;
    QLabel* fileNameLabel;
    QLabel* lastResultLabel;

    Ui::CalcLog *ui;

};

#endif // CALCLOG_H
