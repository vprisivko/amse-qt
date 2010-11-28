#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QTimerEvent>

#include "timersdialog.h"
#include "ui_timersdialog.h"

TimersDialog::TimersDialog(QWidget * parent): QDialog(parent),
            ui(new Ui::TimersDialog), timer(0){
    ui->setupUi(this);
    setWindowTitle("Simple Timers Dialog");
    counter.set(0);
    timerInterval.set(-1);
    connect(ui->setB, SIGNAL(clicked()), SLOT(setTimer()));
    connect(ui->stopB, SIGNAL(clicked()), SLOT(stopTimer()));
    connect(&counter, SIGNAL(changed(int)), SLOT(counterChanged(int)));
}

TimersDialog::~TimersDialog() {
    delete ui;
}

void TimersDialog::counterChanged(int value) {
    ui->countVal->setText(QString::number(value));
}

void TimersDialog::setTimer() {
    int newInterval = ui->intervalEdit->text().toInt();
    if(newInterval == 0) return;

    stopTimer();
    ui->intervalVal->setText(QString::number(newInterval));

    timerInterval.set(newInterval);

    timer = new TimerThread(&timerInterval, &counter);
    timer->start();
}

void TimersDialog::stopTimer() {
    if (timer != 0) {
        timerInterval.set(-1);
        timer->terminate();
        timer = 0;
    }
}
