#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSettings>
#include "Calculator.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createWidgets();
    void addWidgets();
    void connectWidgets();
public slots:
    void showCalc(bool vis);
    void writeCalcLine(QString str, double res);
    void openFile();
    void saveFile();
    void revertFile();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
public:
    QLabel *nameLog;
    QLabel *resultLabel;
    QString currentFile;
    Calculator *calcDialog;
    QString historyFile;
    QString fileResult;
    QSettings *settings;

};

#endif // MAINWINDOW_H
