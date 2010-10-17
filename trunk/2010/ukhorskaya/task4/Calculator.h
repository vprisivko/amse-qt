#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QtGui/QMainWindow>
#include "QDialog"
#include "QLabel"
#include "QLineEdit"

class Calculator : public QMainWindow
{
    Q_OBJECT

private:
    //Calculator
    QDialog *calcDialog;
    QLineEdit *lineEdit;

    //LogWidget
    QLabel *centralLabel;

    //File
    QString fileContent;
    QString fileName;
    double lastValue;

    //StatusBar
    QLabel *resultLabel;
    QLabel *fileNameLabel;

private:
    void createMenu();
    void createCalculator();
    void createLogWidget();
    void createStatusBar();

public:
    Calculator(QWidget *parent = 0);

public slots:
    void calcPressed();
    void calcButtonPressed();

    void openFile(bool);
    void saveFile();
    void revertFile();
};

#endif // CALCULATOR_H
