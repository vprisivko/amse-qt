#ifndef _Dialog_
#define _Dialog_
#include <QWidget>
#include <QDialog>
#include <QTimerEvent>
#include<QPushButton>
#include<QLineEdit>
#include<QComboBox>
#include<QTimer>
#include<QEvent>
#include<QLabel>

class Dialog: public QDialog {

  Q_OBJECT;
  private:
    int timer_id1,timer_id2;
    int time1,time2;
    int period1,period2;
    QLabel* timerLabel1;
    QLabel* timerLabel2;
    QComboBox* Combo;
    QPushButton* set;
    QPushButton* stop;
    QLineEdit* setline;
    
   
  
  public:  
    Dialog(QWidget *parent = 0);
    
    void timerEvent(QTimerEvent* e);
    
  public slots:
    void setTimer();
    void stopTimer();
    
  friend class Test;

};
    
    

#endif
