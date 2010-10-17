#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QMainWindow>
#include <QMenuBar>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QStatusBar>
#include <QTextEdit>

class MainWindow : public QMainWindow {
    Q_OBJECT;

private:
    QString fileName;
    double lastResult;

    QMenuBar *myMenu;
    QMenu *fileMenu;
    QAction *open;
    QAction *save;
    QAction *revert;
    QAction *close;
    QAction *calculator;

    QDialog *calcDialog;
    QVBoxLayout *vLay;
    QLineEdit *edit;
    QHBoxLayout *hLay;
    QPushButton *bnPlus;
    QPushButton *bnMinus;
    QPushButton *bnTimes;
    QPushButton *bnDivide;

    QLabel *lFileName;
    QLabel *lLastResult;

    QTextEdit *textEdit;

private:
    void makeMenu();
    void makeStatusBar();
    void makeCentralWidget();
    void makeCalcWidget();
    void connections();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void sopen();
    void ssave();
    void srevert();
    void sclose();
    void scalculator();

    void minus();
    void plus();
    void times();
    void divide();
};

#endif // _MAINWINDOW_H_
