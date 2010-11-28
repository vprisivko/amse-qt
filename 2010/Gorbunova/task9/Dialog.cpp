
#include "Dialog.h"
#include<QHBoxLayout>
#include<QVBoxLayout>

Dialog::Dialog(QWidget *parent): QDialog(parent){
  acriveTimer = 0;
  
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
  set = new QPushButton("Set", this);
  setLayout->addWidget(set);
  this->layout()->addItem(setLayout);
  
  stop = new QPushButton( "Stop", this);
  this->layout()->addWidget(stop);
  connect(Combo,SIGNAL(currentIndexChanged(int)),this, SLOT(setTimer(int)));
  connect(set, SIGNAL(clicked()), this, SLOT(setCount()));
  connect(stop, SIGNAL(clicked()), this, SLOT(stopTimer()));

  startTimer(10);
}

void Dialog::timerEvent(QTimerEvent*){
  myThread1.lock();
  timerLabel1->setText(QString::number(period1));
  myThread1.unlock();
  myThread2.lock();
  timerLabel2->setText(QString::number(period2));
  myThread2.unlock();
}

void Dialog::setTimer(int index){
  acriveTimer = index;
}

void Dialog::stopTimer(){
 if (acriveTimer == 0) {
   if (time1.isRunning()) {
     time1.terminate();
   }
 }
 if ( acriveTimer == 1) {
   if (time2.isRunning()) {
     time2.terminate();
   }
 }
}
void Dialog::setCount(){
 if (acriveTimer == 0) {
   if( setline->text().toInt() != 0 ){  
     time1.set(setline->text().toInt(), &period1, &myThread1);
     time1.start(); 
   }
  } 
  else {
    
   if( setline->text().toInt() != 0 ){  
     time2.set(setline->text().toInt(), &period2, &myThread2);
     time2.start(); 
   }
  }
}


  

  
  


  
  

  
  
