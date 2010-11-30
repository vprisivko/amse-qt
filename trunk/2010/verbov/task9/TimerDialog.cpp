#include <QVBoxLayout>
#include <QHBoxLayout>
#include "TimerDialog.h"

TimerDialog::TimerDialog(QWidget *parent) : QDialog(parent) {
    myFirstTimerValue = mySecondTimerValue = 0;
    myCurrentThread = 0;
    myFirstLocker = new QMutex();
    mySecondLocker = new QMutex();
    setLayout(new QVBoxLayout());

    myFirstTimerLabel = new QLabel("Timer 1: 0", this);
    mySecondTimerLabel = new QLabel("Timer 2: 0", this);
    myTimersList = new QComboBox(this);
    myTimersList->addItem("Timer 1");
    myTimersList->addItem("Timer 2");
    myTimerIntervalLineEdit = new QLineEdit("1000", this);
    mySetButton = new QPushButton("Set", this);
    myStopButton = new QPushButton("Stop", this);

    layout()->addWidget(myFirstTimerLabel);
    layout()->addWidget(mySecondTimerLabel);
    layout()->addWidget(myTimersList);
    QHBoxLayout *intervalLayout = new QHBoxLayout();
    intervalLayout->addWidget(myTimerIntervalLineEdit);
    intervalLayout->addWidget(mySetButton);
    layout()->addItem(intervalLayout);
    layout()->addWidget(myStopButton);

    connect(mySetButton, SIGNAL(pressed()),
            this, SLOT(setTimer()));
    connect(myStopButton, SIGNAL(pressed()),
            this, SLOT(stopTimer()));
    startTimer(1);
}

TimerDialog::~TimerDialog() {
    delete myFirstLocker;
    delete mySecondLocker;
}

void TimerDialog::timerEvent(QTimerEvent *) {
    QString value;
    myFirstLocker->lock();
    myFirstTimerLabel->setText("Timer 1: " + value.setNum(myFirstTimerValue));
    myFirstLocker->unlock();
    mySecondLocker->lock();
    mySecondTimerLabel->setText("Timer 2: " + value.setNum(mySecondTimerValue));
    mySecondLocker->unlock();
}

void TimerDialog::setTimer() {
    int interval = myTimerIntervalLineEdit->text().toInt();
    myCurrentThread = myTimersList->currentIndex();
    terminateCurrentThread();
    if (myCurrentThread == 0) {
        myFirstThread.set(interval, &myFirstTimerValue, myFirstLocker);
        myFirstThread.start();
    } else {
        mySecondThread.set(interval, &mySecondTimerValue, mySecondLocker);
        mySecondThread.start();
    }
}

void TimerDialog::terminateCurrentThread() {
    if (myCurrentThread == 0) {
        if (myFirstThread.isRunning()) {
            myFirstThread.terminate();
        }
    } else {
        if (mySecondThread.isRunning()) {
            mySecondThread.terminate();
        }
    }
}

void TimerDialog::stopTimer() {
    myCurrentThread = myTimersList->currentIndex();
    terminateCurrentThread();
}
