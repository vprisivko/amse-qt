#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QTimerEvent>

#include "timersdialog.h"

TimersDialog::TimersDialog(QWidget * parent): QDialog(parent),timer1Counter(0),
        timer2Counter(0),timer1Interval(1000),timer2Interval(1000),nowEditTimer(0) {
    setWindowTitle("Simple Timers Dialog");
    QVBoxLayout * mainlo = new QVBoxLayout(this);
    //labels
    QHBoxLayout * firstTimerLabelLayout = new QHBoxLayout();
    timer1Label = new QLabel(QString::number(timer1Counter),this);
    firstTimerLabelLayout->addWidget(new QLabel("<i>timer1<i>",this));
    firstTimerLabelLayout->addWidget(timer1Label);
    mainlo->addLayout(firstTimerLabelLayout);
    QHBoxLayout * secondTimerLabelLayout = new QHBoxLayout();
    timer2Label = new QLabel(QString::number(timer2Counter),this);
    secondTimerLabelLayout->addWidget(new QLabel("<i>timer2<i>",this));
    secondTimerLabelLayout->addWidget(timer2Label);
    mainlo->addLayout(secondTimerLabelLayout);
    //labesl end
    //combo
    QComboBox * combo = new QComboBox(this);
    combo->insertItem(0,"timer1");
    combo->insertItem(1,"timer2");
    connect(combo,SIGNAL(currentIndexChanged(int)),this,SLOT(changeTimerEditLayout(int)));
    mainlo->addWidget(combo);
    //combo end
    //interval settings
    intervalEdit = new QLineEdit("1000",this);
    QHBoxLayout * intervalLayout = new QHBoxLayout();
    QPushButton * setButton = new QPushButton("Set",this);
    QPushButton * stopButton = new QPushButton("Stop",this);
    connect(setButton,SIGNAL(clicked()),this,SLOT(setTimerBC()));
    connect(stopButton,SIGNAL(clicked()),this,SLOT(stopTimerBC()));
    intervalLayout->addWidget(intervalEdit);
    intervalLayout->addWidget(setButton);
    mainlo->addLayout(intervalLayout);
    mainlo->addWidget(stopButton);
    setLayout(mainlo);
    //interval settings end
}

void TimersDialog::timerEvent(QTimerEvent * event) {
    int tid = event->timerId();
    if(tid == timerId1)
        timer1Label->setText(QString::number(++timer1Counter));
    else if(tid == timerId2)
        timer2Label->setText(QString::number(++timer2Counter));
}

void TimersDialog::changeTimerEditLayout(int timerNum) {
    if (nowEditTimer == timerNum) return;
    nowEditTimer = timerNum;
    if (timerNum == 0) {
        intervalEdit->setText(QString::number(timer1Interval));
    }
    if (timerNum == 1) {
        intervalEdit->setText(QString::number(timer2Interval));
    }
}

void TimersDialog::setTimerBC() {
    int newInterval = intervalEdit->text().toInt();
    if(newInterval == 0) return;
    stopTimerBC();
    if (nowEditTimer == 0) {
        timerId1 = startTimer(newInterval);
        timer1Interval = newInterval;
    }
    if (nowEditTimer == 1) {
        timerId2 = startTimer(newInterval);
        timer2Interval = newInterval;
    }
}

void TimersDialog::stopTimerBC() {
    if (nowEditTimer == 0) {
        if(timerId1 != 0) killTimer(timerId1);
        timerId1 = 0;
    }
    if (nowEditTimer == 1) {
        if(timerId2 != 0) killTimer(timerId2);
        timerId2 = 0;
    }
}
