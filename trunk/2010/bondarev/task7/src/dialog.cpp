#include <QDebug>
#include "dialog.h"

Dialog::Dialog(QWidget *parent):
        QDialog(parent),
        counterTimer1(0),
        counterTimer2(0) {
    leInterval = new QLineEdit(this);
    btnSetInterval = new QPushButton("Set", this);

    lay1 = new QHBoxLayout();
    lay1->addWidget(leInterval);
    lay1->addWidget(btnSetInterval);


    lTimer1 = new QLabel("Timer 1:", this);
    lTimer1Counter = new QLabel(QString::number(counterTimer1), this);

    layTimer1 = new QHBoxLayout();
    layTimer1->addWidget(lTimer1);
    layTimer1->addWidget(lTimer1Counter);

    lTimer2 = new QLabel("Timer 2:", this);
    lTimer2Counter = new QLabel(QString::number(counterTimer2), this);

    layTimer2 = new QHBoxLayout();
    layTimer2->addWidget(lTimer2);
    layTimer2->addWidget(lTimer2Counter);

    cmbCheckTimer = new QComboBox(this);
    cmbCheckTimer->addItem("Timer1");
    cmbCheckTimer->addItem("Timer2");
    btnStop = new QPushButton("Stop", this);

    lMain = new QVBoxLayout(this);
    lMain->addItem(layTimer1);
    lMain->addItem(layTimer2);
    lMain->addWidget(cmbCheckTimer);
    lMain->addItem(lay1);
    lMain->addWidget(btnStop);
    this->setLayout(lMain);

    this->connect(btnSetInterval, SIGNAL(pressed()), this, SLOT(set()));
    this->connect(btnStop, SIGNAL(pressed()), this, SLOT(stop()));

    this->setWindowTitle("Task2. Bondarev");
}

Dialog::~Dialog() {
    delete lMain;
    delete lay1;
    delete lTimer1;
    delete lTimer2;
    delete cmbCheckTimer;
    delete leInterval;
    delete btnSetInterval;
    delete btnStop;
}

void Dialog::timerEvent(QTimerEvent *e) {
    int id = e->timerId();
    if (id == idTimer1) {
        lTimer1Counter->setText(QString::number(++counterTimer1));
    } else if (id == idTimer2) {
        lTimer2Counter->setText(QString::number(++counterTimer2));
    }
}

void Dialog::set() {
    int currentTimer = cmbCheckTimer->currentIndex();
    if (currentTimer == 0) {
        idTimer1 = startTimer(leInterval->text().toInt());
    } else if (currentTimer == 1) {
        idTimer2 = startTimer(leInterval->text().toInt());
    }

}

void Dialog::stop() {
    int currentIndex = cmbCheckTimer->currentIndex();
    if (currentIndex == 0) {
        killTimer(idTimer1);
    } else if (currentIndex == 1) {
        killTimer(idTimer2);
    }
}
