#ifndef _MYWINDOW_
#define _MYWINDOW_


#include "MyCalc.h"
#include <QMainWindow>
#include <QAction>
#include <QTextEdit>
#include <QDockWidget>
#include <QString>
#include <QLabel>

class myWindow: public QMainWindow{
  Q_OBJECT;
  
  public:
    myWindow(QWidget* parent = 0);
    
  private:
    QTextEdit* CentralText;
    QLabel* nameLabel;
    QLabel* resultLabel;
    myCalc* c;
    QAction* Open;
    QAction* Save;
    QAction* Revert;
    QAction* calcul;
    double lastResult;
    
    QString myName;
  
  private:
    void connection();
    void makeAction();  
    void makeMenu();
    void makeToolbar();
    void makeCentralText();
    void makeStatusBar();
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

#endif
