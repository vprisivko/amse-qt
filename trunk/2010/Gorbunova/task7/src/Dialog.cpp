
#include "Dialog.h"
#include<QHBoxLayout>
#include<QVBoxLayout>

Dialog::Dialog(QWidget *parent): QDialog(parent){
  time1 = 0;
  time2 = 0;
  period1 = 0;
  period2 = 0;
  this->setLayout( new QVBoxLayout());
  
  QHBoxLayout* timer1out = new QHBoxLayout();
  timerLabel1 = new QLabel("0",this);
  timer1out->addWidget(new QLabel("Timer 1 : ",this));
  timer1out->addWidget(timerLabel1);
  this->layout()->addItem(timer1out);
  
  QHBoxLayout* timer2out = new QHBoxLayout();
  timerLabel2 = new QLabel("0",this);
  timer2out->addWidget(new QLabel("Timer 2 : ",this));
  timer2out->addWidget(timerLabel2);
  this->layout()->addItem(timer2out);
  
  Combo = new QComboBox( this );
  Combo->addItem( "Timer1" );
  Combo->addItem( "Timer2" );
  this->layout()->addWidget(Combo);

  QHBoxLayout *setLayout = new QHBoxLayout();
  setline = new QLineEdit(this);
  setLayout->addWidget(setline);
  set = new QPushButton( "Set", this);
  setLayout->addWidget(set);
  this->layout()->addItem(setLayout);
  
  stop = new QPushButton( "Stop", this);
  this->layout()->addWidget(stop);
  
  connect(set, SIGNAL(clicked()), this, SLOT(setTimer()));
  connect(stop, SIGNAL(clicked()), this, SLOT(stopTimer()));
}

void Dialog::timerEvent(QTimerEvent* e){
  if (e->timerId() == timer_id1){
    timerLabel1->setText(QString::number(++time1));
  }
  else{
    if (e->timerId() == timer_id2){
      timerLabel2->setText(QString::number(++time2));
    }
  }
}

void Dialog::setTimer(){
  int interval = setline->text().toInt();
  if (Combo->currentIndex() == 0){
    if (timer_id1 != 0){
      killTimer(timer_id1);
    }
    timer_id1 = startTimer(interval);
  } 
  else{
    if (timer_id2 != 0){
      killTimer(timer_id2);
    }
    timer_id2 = startTimer(interval);
  }
}

void Dialog::stopTimer(){
  if (Combo->currentIndex() == 0) {
   if (timer_id1 != 0) {
     killTimer(timer_id1);
     timer_id1 = 0;
    }
  } 
  else {
    if (timer_id2 != 0) {
      killTimer(timer_id2);
        timer_id2 = 0;
      }
  }
}



  

  
  


  
  

  
  
