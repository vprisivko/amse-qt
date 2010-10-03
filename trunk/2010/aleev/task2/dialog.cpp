#include "dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent){
    firstTimeCounter = 0;
    secondTimeCounter = 0;
    firstTimer_id = 0;
    secondTimer_id = 0;

    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    firstLabel = new QLabel("0",this);
    secondLabel = new QLabel("0",this);

    firstLabelLayout = new QHBoxLayout();
    firstLabelLayout->addWidget(new QLabel("Timer 1 : ",this));
    firstLabelLayout->addWidget(firstLabel);
    mainLayout->addLayout(firstLabelLayout);

    secondLabelLayout = new QHBoxLayout();
    secondLabelLayout->addWidget(new QLabel("Timer 2 : ",this));
    secondLabelLayout->addWidget(secondLabel);
    mainLayout->addLayout(secondLabelLayout);

    timersComboBox = new QComboBox(this);
    timersComboBox->addItem("Timer 1");
    timersComboBox->addItem("Timer 2");
    mainLayout->addWidget(timersComboBox);

    setIntervalLineEdit = new QLineEdit(this);
    setButton = new QPushButton("Set", this);

    setIntervalLayout = new QHBoxLayout;
    setIntervalLayout->addWidget(setIntervalLineEdit);
    setIntervalLayout->addWidget(setButton);
    mainLayout->addLayout(setIntervalLayout);

    stopButton = new QPushButton("Stop", this);
    mainLayout->addWidget(stopButton);

    connect(setButton, SIGNAL(clicked()), this, SLOT(setTimer()));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stopTimer()));
}

void Dialog::timerEvent(QTimerEvent *e){
    int currentId = e->timerId();
    if (currentId == firstTimer_id){
        firstLabel->setText(QString::number(++firstTimeCounter));
    }
    else{
        if (currentId == secondTimer_id){
            secondLabel->setText(QString::number(++secondTimeCounter));
        }
    }
}

void Dialog::setTimer(){
    int interval = setIntervalLineEdit->text().toInt();
    if (interval == 0){
        return;
    }
    if (timersComboBox->currentIndex() == 0){
        if (firstTimer_id != 0){
            killTimer(firstTimer_id);
        }
        firstTimer_id = startTimer(interval);
    } else{
        if (secondTimer_id != 0){
            killTimer(secondTimer_id);
        }
        secondTimer_id = startTimer(interval);
    }
}

void Dialog::stopTimer(){
    if (timersComboBox->currentIndex() == 0) {
        if (firstTimer_id != 0) {
            killTimer(firstTimer_id);
            firstTimer_id = 0;
        }
    } else {
        if (secondTimer_id != 0) {
            killTimer(secondTimer_id);
            secondTimer_id = 0;
        }
    }
}


