#include "Dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
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
  my_label1 = new QLabel("0", this);
  l->addWidget(my_label1);
  layout()->addItem(l);

  l = new QHBoxLayout();
  l->addWidget(new QLabel("Timer 2: ", this));
  my_label2 = new QLabel("0", this);
  l->addWidget(my_label2);
  layout()->addItem(l);

  my_cbox = new QComboBox(this);
  my_cbox->addItem("Timer 1");
  my_cbox->addItem("Timer 2");
  connect(my_cbox, SIGNAL(currentIndexChanged(int)),
          this, SLOT(cboxchanged(int)));
  layout()->addWidget(my_cbox);

  l = new QHBoxLayout();
  my_edit = new QLineEdit("0", this);
  my_setbtn = new QPushButton("Set", this);
  connect(my_setbtn, SIGNAL(clicked()),
          this, SLOT(btnset()) );
  l->addWidget(my_edit);
  l->addWidget(my_setbtn);
  layout()->addItem(l);

  my_stopbtn = new QPushButton("Stop", this);
  connect(my_stopbtn, SIGNAL(clicked()),
          this, SLOT(btnstop()) );
  layout()->addWidget(my_stopbtn);
}

void Dialog::timerEvent(QTimerEvent* e) {
  if (timer1.id == e->timerId()) {
    my_label1->setText(QString::number(++timer1.time));
  }
  if (timer2.id == e->timerId()) {
    my_label2->setText(QString::number(++timer2.time));
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
    timer1.id = startTimer(my_edit->text().toInt());
  }
  if (activetimer == 1) {
    if (timer2.id != 0) killTimer(timer2.id);
    timer2.id = startTimer(my_edit->text().toInt());
  }
  emit setSignal();
}

