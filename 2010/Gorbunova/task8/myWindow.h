#ifndef MYWINDOW_H
#define MYWINDOW_H
#include <QDockWidget>
#include <QString>
#include <QLabel>
#include <QMainWindow>
#include "MyCalc.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    QLabel* nameLabel;
    QLabel* resultLabel;
    myCalc* c;
    QString myName;
    double lastResult;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    void connection();
public slots:
   void Calc();
   void Add();
   void Sub();
   void Mul();
   void Div();
   void fileOpen();
   void fileSave();
   void fileRevert();
};

#endif // MYWINDOW_H
