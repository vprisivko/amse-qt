#include <QApplication>

#include "TimeDialog.h"

TimeDialog::TimeDialog(QWidget* parent) :QDialog(parent){
  
  myfirsttimerid=0;
  mysecondtimerid=0;
  myfirsttime=0;
  mysecondtime=0;

  myfirsttimelabel = new QLabel("0",this);
  mysecondtimelabel = new QLabel("0",this);

  mybox = new QComboBox(this);      qApp->quit();
  mybox->addItem("timer1");
  mybox->addItem("timer2");
  
  myset = new QLineEdit(this);

  QLabel* firsttimer = new QLabel("timer1",this);
  QLabel* secondtimer = new QLabel("timer2",this);

  QPushButton* setbutton = new QPushButton("Set",this);
  QPushButton* stopbutton = new QPushButton("Stop",this);

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
  setlayout->addWidget(setbutton);

  layout()->addWidget(stopbutton);
  QObject::connect(setbutton, SIGNAL(clicked()), this ,SLOT(Set()));
  QObject::connect(stopbutton, SIGNAL(clicked()), this ,SLOT(Stop()));
}

void TimeDialog::Set(){
  if (!myset->text().isEmpty()){
    if (mybox->currentIndex() == 0) {
      if (myfirsttimerid != 0) {
        killTimer(myfirsttimerid);
      }
      myfirsttimerid = startTimer(myset->text().toInt());
    } else {
      if (mybox->currentIndex() == 1) {
        if (mysecondtimerid != 0) {
          killTimer(mysecondtimerid);
        }
        mysecondtimerid = startTimer(myset->text().toInt());
      }
    }
  }
}

void TimeDialog::Stop(){
  if (mybox->currentIndex() == 0) {
    if (myfirsttimerid != 0) {
      killTimer(myfirsttimerid);
    }
    myfirsttimerid = 0;
  } else {
    if (mybox->currentIndex() == 1) {
      if (mysecondtimerid != 0) {
        killTimer(mysecondtimerid);
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
