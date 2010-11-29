#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Calculator.h"
#include <QMainWindow>
#include <QLabel>
#include <QTextEdit>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Calculator *calc;
    QString logHistory;
    QString lastResultHistory;
    QLabel *filenameLabel;
    QLabel *lastResultLabel;

public slots:
    void addToLog(QString str, double res);
    void openFile();
    void saveFile();
    void revertFile();
    void showCalculator(bool isChecked);
};

#endif // MAINWINDOW_H
