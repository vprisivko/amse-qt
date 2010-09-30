#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QDebug>
#include <QTimerEvent>
#include <QFont>
#include <QIcon>
#include "dialog.h"


Dialog::Dialog(QWidget *parent)
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

    //Buttons
    intervalLineEdit = new QLineEdit(this);
    setButton = new QPushButton("set", this);
    setButton->setFont(f);
    setButton->setIcon(QIcon("filesave.xpm"));
    stopButton = new QPushButton("stop", this);

    connect(stopButton, SIGNAL(pressed()), this, SLOT(stopTimer()));
    connect(setButton, SIGNAL(pressed()), this, SLOT(setTimer()));

    firstTimerCounter = 0;
    secondTimerCounter = 0;

    layout()->addWidget(changeTimerComboBox);

    QHBoxLayout *intervalLayout = new QHBoxLayout();
    intervalLayout->addWidget(intervalLineEdit);
    intervalLayout->addWidget(setButton);
    layout()->addItem(intervalLayout);

    layout()->addWidget(stopButton);

    this->show();
}

Dialog::~Dialog()
{

}

void Dialog::timerEvent(QTimerEvent *e) {
   if (e->timerId() == firstTimerId) {
        firstTimerCounter++;
        QString tmp = "";
        tmp.setNum(firstTimerCounter);
        firstTimerNumberLabel->setText(tmp);
    }
    if (e->timerId() == secondTimerId) {
        secondTimerCounter++;
        QString tmp = "";
        tmp.setNum(secondTimerCounter);
        secondTimerNumberLabel->setText(tmp);
    }
}

void Dialog::setTimer()
{
  qDebug() << firstTimerId << " - " << secondTimerId << " - " << changeTimerComboBox->currentIndex();
  QString tmp = intervalLineEdit->text();
    if (!tmp.isEmpty()) {
        switch (changeTimerComboBox->currentIndex()) {
            case 0: {
              killTimer(firstTimerId);
              firstTimerId = startTimer(tmp.toInt());
              break;
            }
            case 1: {
              killTimer(secondTimerId);
              secondTimerId = startTimer(tmp.toInt());
              break;
            }
        }
    }
}

void Dialog::stopTimer()
{
    switch(changeTimerComboBox->currentIndex()) {
        case 0: {
            killTimer(firstTimerId);
            break;
        }
        case 1: {
            killTimer(secondTimerId);
            break;
        }
    }
}
