#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QDebug>
#include <QTimerEvent>
#include <QFont>
#include <QIcon>
#include "TimerDialog.h"


TimerDialog::TimerDialog(QWidget *parent)
    : QDialog(parent)
{
    setLayout(new QVBoxLayout());

    //Labels for timers with counter
    firstTimerTextLabel = new QLabel("timer 1:", this);
    firstTimerTextLabel->setAlignment(Qt::AlignCenter);
    QFont f("Courier", 12, 75);
    f.setUnderline(TRUE);
    firstTimerTextLabel->setFont(f);

    secondTimerTextLabel = new QLabel("timer 2:", this);
    secondTimerTextLabel->setAlignment(Qt::AlignCenter);

    firstTimerNumberLabel = new QLabel("0", this);
    firstTimerNumberLabel->setFont(f);

    secondTimerNumberLabel = new QLabel("0", this);

    QHBoxLayout *firstTimerLayout = new QHBoxLayout();
    firstTimerLayout->addWidget(firstTimerTextLabel);
    firstTimerLayout->addWidget(firstTimerNumberLabel);
    layout()->addItem(firstTimerLayout);

    QHBoxLayout *secondTimerLayout = new QHBoxLayout();
    secondTimerLayout->addWidget(secondTimerTextLabel);
    secondTimerLayout->addWidget(secondTimerNumberLabel);
    layout()->addItem(secondTimerLayout);

    //Combobox
    changeTimerComboBox = new QComboBox();
    changeTimerComboBox->addItem("timer 1");
    changeTimerComboBox->addItem("timer 2");
    connect(changeTimerComboBox, SIGNAL(activated(int)), this, SLOT(changeCurrentTimer()));


    //Buttons
    intervalLineEdit = new QLineEdit(this);
    setButton = new QPushButton("set", this);
    setButton->setFont(f);
    stopButton = new QPushButton("stop", this);

    connect(stopButton, SIGNAL(pressed()), this, SLOT(stopTimer()));
    connect(setButton, SIGNAL(pressed()), this, SLOT(setTimer()));

    timerThread1 = 0;
    timerThread2 = 0;
    timer = new QTimer(this);
    currentTimerId = 0;

    connect(timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
    timer -> start(100);

    layout()->addWidget(changeTimerComboBox);

    QHBoxLayout *intervalLayout = new QHBoxLayout();
    intervalLayout->addWidget(intervalLineEdit);
    intervalLayout->addWidget(setButton);
    layout()->addItem(intervalLayout);

    layout()->addWidget(stopButton);

    firstTimerCounter = 0;
    secondTimerCounter = 0;

    this->show();
}

TimerDialog::~TimerDialog()
{

}

void TimerDialog::timerEvent() {
    if (timerThread1 != 0){
        timerThread1-> mutex.lock();
        firstTimerNumberLabel -> setText(QString::number(firstTimerCounter));
        timerThread1 -> mutex.unlock();
    }
    if (timerThread2 != 0){
        timerThread2 -> mutex.lock();
        secondTimerNumberLabel -> setText(QString::number(secondTimerCounter));
        timerThread2 -> mutex.unlock();
    }
}

void TimerDialog::setTimer()
{
  int interval = intervalLineEdit->text().toInt();
  if(currentTimerId == 0) {
        if(timerThread1 != 0){
            timerThread1-> terminate();
            delete timerThread1;
            timerThread1 = 0;
        }
        timerThread1 = new TimerThread(interval, &firstTimerCounter);
        timerThread1 -> start();
   } else {
        if(timerThread2 != 0){
           timerThread2 -> terminate();
           delete timerThread2;
           timerThread2 = 0;
        }
        timerThread2 = new TimerThread(interval, &secondTimerCounter);
        timerThread2 -> start();
   }
}

void TimerDialog::stopTimer()
{
    if(currentTimerId == 0) {
        if(timerThread1 != 0) {
         timerThread1 -> terminate();
         delete timerThread1;
         timerThread1 = 0;
        }
    }
    else {
        if(timerThread2 != 0) {
         timerThread2 -> terminate();
         delete timerThread2;
         timerThread2 = 0;
        }

    }
}

void TimerDialog::changeCurrentTimer() {
    currentTimerId = changeTimerComboBox -> currentIndex();
}
