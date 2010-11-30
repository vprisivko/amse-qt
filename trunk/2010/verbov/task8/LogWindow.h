#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "CalculatorDialog.h"

namespace Ui {
    class LogWindow;
}

class LogWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogWindow(QWidget *parent = 0);
    ~LogWindow();

public slots:
        void fileOpen();
        void fileSave();
        void revert();
        void runCalculator();
        void updateResult(double result);

private:
        void readFile();

private:
    Ui::LogWindow *ui;
    QLabel *filenameLabel, *resultLabel;
    CalculatorDialog *calculator;
    QString filename;
    double lastResult;
};

#endif // LOGWINDOW_H
