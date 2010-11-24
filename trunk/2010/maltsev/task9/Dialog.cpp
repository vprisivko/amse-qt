#include "Dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QtDebug>

Dialog::Dialog(QWidget *parent): QDialog(parent) {
    activetimer = 0;
    c1 = c2 = 0;

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

    startTimer(10);
}

void Dialog::timerEvent(QTimerEvent*) {
    lock1.lock();
    lb1->setText(QString::number(c1));
    lock1.unlock();
    lock2.lock();
    lb2->setText(QString::number(c2));
    lock2.unlock();
}

void Dialog::cboxchanged(int index) {
    activetimer = index;
}

void Dialog::btnstop() {
    if (activetimer == 0) {
        if (t1.isRunning()) {
            t1.terminate();;
        }
    }
    if (activetimer == 1) {
        if (t2.isRunning()) {
            t2.terminate();
        }
    }
}

void Dialog::btnset() {
    if (activetimer == 0) {
        if (t1.isRunning()) {
            t1.terminate();;
        }
        if (ed->text().toInt() != 0) {
            t1.set(ed->text().toInt(), &c1, &lock1);
            t1.start();
        }
    }
    if (activetimer == 1) {
        if (t2.isRunning()) {
            t2.terminate();
        }
        if (ed->text().toInt() != 0) {
            t2.set(ed->text().toInt(), &c2, &lock2);
            t2.start();
        }
    }
}

