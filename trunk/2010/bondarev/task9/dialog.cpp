#include <QDebug>
#include "dialog.h"

Dialog::Dialog(QWidget *parent): QDialog(parent) {
    makeWidget();

    counter1 = 0;
    counter2 = 0;

    t1 = t2 = 0;

    startTimer(10);

    this->connect(btnSetInterval, SIGNAL(pressed()), this, SLOT(set()));
    this->connect(btnStop, SIGNAL(pressed()), this, SLOT(stop()));

    this->setWindowTitle("Task9. Bondarev");
}

void Dialog::makeWidget() {
    leInterval = new QLineEdit(this);
    btnSetInterval = new QPushButton("Set", this);

    lay1 = new QHBoxLayout();
    lay1->addWidget(leInterval);
    lay1->addWidget(btnSetInterval);

    lTimer1 = new QLabel("Timer 1:", this);
    lTimer1Counter = new QLabel("0", this);

    layTimer1 = new QHBoxLayout();
    layTimer1->addWidget(lTimer1);
    layTimer1->addWidget(lTimer1Counter);

    lTimer2 = new QLabel("Timer 2:", this);
    lTimer2Counter = new QLabel("0", this);

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

void Dialog::timerEvent(QTimerEvent *) {
    lock1.lock();
    lTimer1Counter->setText(QString::number(counter1));
    lock1.unlock();
    lock2.lock();
    lTimer2Counter->setText(QString::number(counter2));
    lock2.unlock();
}

void Dialog::set() {
    int currentTimer = cmbCheckTimer->currentIndex();
    if (currentTimer == 0) {
        if (t1 && t1->isRunning()) {
            t1->terminate();
        }
        t1 = new Timer(leInterval->text().toInt(), &counter1, &lock1);
        t1->start();
    } else if (currentTimer == 1) {
        if (t2 && t2->isRunning()) {
            t2->terminate();
        }
        t2 = new Timer(leInterval->text().toInt(), &counter2, &lock2);
        t2->start();
    }
}

void Dialog::stop() {
    int currentIndex = cmbCheckTimer->currentIndex();
    if (currentIndex == 0) {
        if (t1 != 0)
            t1->terminate();
    } else if (currentIndex == 1) {
        if (t2 != 0)
            t2->terminate();
    }
}
