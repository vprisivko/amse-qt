#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QLabel>

#include "Calculator.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Calculator *calc;

    //File
    QString fileContent;
    QString fileName;

    //StatusBar
    QLabel *resultLabel;
    QLabel *fileNameLabel;

    void createStatusBar();

private:
    Ui::MainWindow *ui;

public slots:
    void openFile(bool);
    void saveFile();
    void revertFile();

    void calcPressed();

    void exprCalculated(QString result);

};

#endif // MAINWINDOW_H
