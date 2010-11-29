#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QDialog>
#include <QAction>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT;

private:
    Ui::MainWindow *ui;

    QString fileName;
    double lastResult;
    bool lastResultIsExist;

    QLabel *lFileName;
    QLabel *lLastResult;

    QDialog *calcDialog;
    QLineEdit *edit;
    QPushButton *bnPlus;
    QPushButton *bnMinus;
    QPushButton *bnTimes;
    QPushButton *bnDivide;

    QAction *calculator;

    void makeStatusBar();
    void makeMenu();
    void makeCalcWidget();
    void connections();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void minus();
    void plus();
    void times();
    void divide();

    void sopen();
    void ssave();
    void srevert();
    void sclose();
    void scalculator();
};

#endif // MAINWINDOW_H
