#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimerEvent>

#include "timersdialog.h"

TimersDialog::TimersDialog(QWidget * parent): QDialog(parent),timer1Counter(0),
        timer2Counter(0),timer1Interval(1000),timer2Interval(1000),nowEditTimer(0) {
    setWindowTitle("Simple Timers Dialog");
    generateObjects();
    connectObjects();
}

void TimersDialog::generateObjects() {
    QVBoxLayout * mainlo = new QVBoxLayout(this);
    setLayout(mainlo);

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
    //labels end

    //combo
    combo = new QComboBox(this);
    combo->insertItem(0, "timer1");
    combo->insertItem(1, "timer2");
    mainlo->addWidget(combo);
    //combo end

    //interval settings
    intervalEdit = new QLineEdit("1000",this);
    QHBoxLayout * intervalLayout = new QHBoxLayout();
    setButton = new QPushButton("Set", this);
    stopButton = new QPushButton("Stop", this);
    intervalLayout->addWidget(intervalEdit);
    intervalLayout->addWidget(setButton);
    mainlo->addLayout(intervalLayout);
    mainlo->addWidget(stopButton);
    //interval settings end
}

void TimersDialog::connectObjects() {
    connect(combo, SIGNAL(currentIndexChanged(int)), SLOT(changeTimerEditLayout(int)));
    connect(setButton,  SIGNAL(clicked()), SLOT(setTimerBC()));
    connect(stopButton, SIGNAL(clicked()), SLOT(stopTimerBC()));

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
