#include "dialog.h"
#include <QIntValidator>
#include <QString>

Dialog::Dialog(QWidget *parent) : QDialog(parent), DELAY(50){
    timerCounters[0] = timerCounters[1] = 0;

    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    timerLabels[0] = new QLabel("0",this);
    timerLabels[1] = new QLabel("0",this);

    firstLabelLayout = new QHBoxLayout();
    firstLabelLayout->addWidget(new QLabel("Timer 1 : ",this));
    firstLabelLayout->addWidget(timerLabels[0]);
    mainLayout->addLayout(firstLabelLayout);

    secondLabelLayout = new QHBoxLayout();
    secondLabelLayout->addWidget(new QLabel("Timer 2 : ",this));
    secondLabelLayout->addWidget(timerLabels[1]);
    mainLayout->addLayout(secondLabelLayout);

    timersComboBox = new QComboBox(this);
    timersComboBox->addItem("Timer 1");
    timersComboBox->addItem("Timer 2");
    mainLayout->addWidget(timersComboBox);

    setIntervalLineEdit = new QLineEdit(this);
    setIntervalLineEdit->setValidator(new  QIntValidator());
    setButton = new QPushButton("Set", this);

    setIntervalLayout = new QHBoxLayout;
    setIntervalLayout->addWidget(setIntervalLineEdit);
    setIntervalLayout->addWidget(setButton);
    mainLayout->addLayout(setIntervalLayout);

    stopButton = new QPushButton("Stop", this);
    mainLayout->addWidget(stopButton);

    connect(setButton, SIGNAL(clicked()), this, SLOT(setTimer()));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stopTimer()));
    connect(this, SIGNAL(stopTimerSignal(Timer*)), &timers[0], SLOT(stop(Timer*)));
    connect(this, SIGNAL(stopTimerSignal(Timer*)), &timers[1], SLOT(stop(Timer*)));

    startTimer(DELAY);
}

Dialog::~Dialog() {
    timers[0].terminate();
    timers[1].terminate();
}

void Dialog::timerEvent(QTimerEvent*){
    for(int i=0; i < 2; ++i) {
        mutexes[i].lock();
        QString str = QString::number(timerCounters[i]);
        mutexes[i].unlock();
        timerLabels[i]->setText(str);
    }
}

void Dialog::setTimer(){
    int interval = setIntervalLineEdit->text().toInt();
    if (interval == 0){
        return;
    }
    int curTimer = timersComboBox->currentIndex();
    timers[curTimer].setParams(&timerCounters[curTimer], interval, &mutexes[curTimer]);
    timers[curTimer].start();
}

void Dialog::stopTimer(){
    int curTimer = timersComboBox->currentIndex();
    if (timers[curTimer].isRunning() == false) {
        return;
    }
    emit stopTimerSignal(&timers[curTimer]);
}


