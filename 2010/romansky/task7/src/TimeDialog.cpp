#include <QApplication>

#include "TimeDialog.h"

TimeDialog::TimeDialog(QWidget* parent) :QDialog(parent){
  
  myfirsttimerid=0;
  mysecondtimerid=0;
  myfirsttime=0;
  mysecondtime=0;

  myfirsttimelabel = new QLabel("0",this);
  mysecondtimelabel = new QLabel("0",this);

  mybox = new QComboBox(this);      
  mybox->addItem("timer1");
  mybox->addItem("timer2");
  
  myset = new QLineEdit(this);

  QLabel* firsttimer = new QLabel("timer1",this);
  QLabel* secondtimer = new QLabel("timer2",this);

  mysetbutton = new QPushButton("Set",this);
  mystopbutton = new QPushButton("Stop",this);

  setLayout(new QVBoxLayout());

  QHBoxLayout* firstlayout = new QHBoxLayout();
  QHBoxLayout* secondlayout = new QHBoxLayout();
  
  QHBoxLayout* setlayout = new QHBoxLayout();

  layout()->addItem(firstlayout);
  firstlayout->addWidget(firsttimer);
  firstlayout->addWidget(myfirsttimelabel);

  layout()->addItem(secondlayout);
  secondlayout->addWidget(secondtimer);
  secondlayout->addWidget(mysecondtimelabel);

  layout()->addWidget(mybox);

  layout()->addItem(setlayout);
  setlayout->addWidget(myset);
  setlayout->addWidget(mysetbutton);

  layout()->addWidget(mystopbutton);
  QObject::connect(mysetbutton, SIGNAL(clicked()), this ,SLOT(Set()));
  QObject::connect(mystopbutton, SIGNAL(clicked()), this ,SLOT(Stop()));
}

void TimeDialog::Set(){
  int t;
  if (!myset->text().isEmpty()){
    if (mybox->currentIndex() == 0) {
      if (myfirsttimerid != 0) {
        killTimer(myfirsttimerid);
      }
      t = myset->text().toInt();
      myfirsttimerid = startTimer(t);
      emit(setSignal());
    } else {
      if (mybox->currentIndex() == 1) {
        if (mysecondtimerid != 0) {
          killTimer(mysecondtimerid);
        }
        t = myset->text().toInt();
        mysecondtimerid = startTimer(t);
        emit(setSignal());
      }
    }
  }
}

void TimeDialog::Stop(){
  if (mybox->currentIndex() == 0) {
    if (myfirsttimerid != 0) {
      killTimer(myfirsttimerid);
      emit(stopSignal());
    }
    myfirsttimerid = 0;
  } else {
    if (mybox->currentIndex() == 1) {
      if (mysecondtimerid != 0) {
        killTimer(mysecondtimerid);
        emit(stopSignal());
      }
      mysecondtimerid = 0;
    }
  }
}  

void TimeDialog::timerEvent(QTimerEvent *e){
  if (e->timerId() == myfirsttimerid){
    myfirsttime = myfirsttime+1;
    myfirsttimelabel->setText(QString::number(myfirsttime));
  } else {
    if (e->timerId() == mysecondtimerid){
      mysecondtime = mysecondtime+1;
      mysecondtimelabel->setText(QString::number(mysecondtime));
    }
  }
}

int TimeDialog::getfirsttime(){
  return myfirsttime;
}

int TimeDialog::getsecondtime(){
  return mysecondtime;
}

int TimeDialog::getfirsttimerid(){
  return myfirsttimerid;
}

int TimeDialog::getsecondtimerid(){
  return mysecondtimerid;
}

QPushButton* TimeDialog::getsetbutton(){
  return mysetbutton;
}

QPushButton* TimeDialog::getstopbutton(){
  return mystopbutton;
}

QComboBox* TimeDialog::getbox(){
  return mybox;
}

QLineEdit* TimeDialog::getsetlineedit(){
  return myset;
}

