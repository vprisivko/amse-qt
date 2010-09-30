#include "Dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>

Dialog::Dialog(QWidget *parent): QDialog(parent) {
  timer1.time = 0;
  timer1.id = 0;
  timer2.time = 0;
  timer2.id = 0;
  activetimer = 0;

  setLayout(new QVBoxLayout);
  QHBoxLayout *l = new QHBoxLayout();
  l->addWidget(new QLabel("Timer 1: ", this));
  lb1 = new QLabel("0", this);
  l->addWidget(lb1);
  layout()->addItem(l);

  l = new QHBoxLayout();
  l->addWidget(new QLabel("Timer 2: ", this));
  lb2 = new QLabel("0", this);
  l->addWidget(lb2);
  layout()->addItem(l);

  cb = new QComboBox(this);
  cb->addItem("Timer 1");
  cb->addItem("Timer 2");
  connect(cb, SIGNAL(currentIndexChanged(int)), 
          this, SLOT(cboxchanged(int)));
  layout()->addWidget(cb);

  l = new QHBoxLayout();
  ed = new QLineEdit("0", this);
  QPushButton *pb = new QPushButton("Set", this);
  connect(pb, SIGNAL(clicked()), 
          this, SLOT(btnset()) );
  l->addWidget(ed);
  l->addWidget(pb);
  layout()->addItem(l);

  pb = new QPushButton("Stop", this);
  connect(pb, SIGNAL(clicked()), 
          this, SLOT(btnstop()) );
  layout()->addWidget(pb);
}

void Dialog::timerEvent(QTimerEvent* e) {
  if (timer1.id == e->timerId()) {
    lb1->setText(QString::number(++timer1.time));
  }
  if (timer2.id == e->timerId()) {
    lb2->setText(QString::number(++timer2.time));
  }
}

void Dialog::cboxchanged(int index) {
  activetimer = index;
}

void Dialog::btnstop() {
  if (activetimer == 0) {
    if (timer1.id != 0) {
      killTimer(timer1.id);
      timer1.id = 0;
    }
  }
  if (activetimer == 1) {
    if (timer2.id != 0) {
      killTimer(timer2.id);
      timer2.id = 0;
    }
  }
}

void Dialog::btnset() {
  if (activetimer == 0) {
    if (timer1.id != 0) killTimer(timer1.id);
    timer1.id = startTimer(ed->text().toInt());
  }
  if (activetimer == 1) {
    if (timer2.id != 0) killTimer(timer2.id);
    timer2.id = startTimer(ed->text().toInt());
  }
}

