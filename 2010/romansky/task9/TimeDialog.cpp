#include <QApplication>

#include "TimeDialog.h"

TimeDialog::TimeDialog(QWidget* parent) :QDialog(parent){


  myfirstmutex = new QMutex();
  mysecondmutex = new QMutex();
  mymainmutex = new QMutex();
  myfirstthread = new TimeThread(myfirstmutex);
  mysecondthread = new TimeThread(mysecondmutex);

  myfirsttimelabel = new QLabel("0",this);
  mysecondtimelabel = new QLabel("0",this);

  mybox = new QComboBox(this);
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
  startTimer(10);
}

void TimeDialog::Set(){
  if (!myset->text().isEmpty()){
    if (myset->text().toInt() > 0){
      if (mybox->currentIndex() == 0) {
        myfirstmutex->lock();
        //if (myfirstthread->isRunning()){
          //myfirstthread->terminate();
        //}
        myfirstthread->setPeriod(myset->text().toInt());
        if (! myfirstthread->isRunning()){
          myfirstthread->start();
        }
        myfirstmutex->unlock();
      } else {
          mysecondmutex->lock();
          //if (mysecondthread->isRunning()){
            //mysecondthread->terminate();
          //}
          mysecondthread->setPeriod(myset->text().toInt());
          if (! mysecondthread->isRunning()){
            mysecondthread->start();
          }
          //mysecondthread->start();
          mysecondmutex->unlock();
      }
    }
  }
}

void TimeDialog::Stop(){
  if (mybox->currentIndex() == 0) {
    myfirstthread->terminate();
  } else {
    if (mybox->currentIndex() == 1) {
      mysecondthread->terminate();
    }
  }
}

void TimeDialog::timerEvent(QTimerEvent *){
    mymainmutex->lock();
    myfirsttimelabel->setText(QString::number(myfirstthread->getTime()));
    //myfirstmutex->unlock();
    //mysecondmutex->lock();
    mysecondtimelabel->setText(QString::number(mysecondthread->getTime()));
    mymainmutex->unlock();
}
