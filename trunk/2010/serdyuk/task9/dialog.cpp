// =====================================================================================
// 
//       Filename:  dialog.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  29.09.2010 22:12:19
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#include "dialog.h"
#include <QValidator>

#include <cstdio>

Dialog::Dialog(QWidget *p) : QDialog(p) {
    myMainLayout = new QVBoxLayout;
    setLayout(myMainLayout);

    myLabel1 = new QLabel(QString("<b>Timer 1:</b> %1").arg(0), this);
    myLabel2 = new QLabel(QString("<b>Timer 2:</b> %1").arg(0), this);

    myMainLayout->addWidget(myLabel1);
    myMainLayout->addWidget(myLabel2);

    myComboBox = new QComboBox(this);
    myComboBox->addItem("Timer 1");
    myComboBox->addItem("Timer 2");

    myMainLayout->addWidget(myComboBox);

    mySetLineEdit = new QLineEdit(this);
    mySetLineEdit->setValidator(new QIntValidator());
    mySetButton = new QPushButton("Set", this);

    mySetLayout = new QHBoxLayout;

    mySetLayout->addWidget(mySetLineEdit);
    mySetLayout->addWidget(mySetButton);

    myMainLayout->addLayout(mySetLayout);

    myStopButton = new QPushButton("Stop", this);

    myMainLayout->addWidget(myStopButton);

    myTimer1 = 0;
    myTimer2 = 0;

    myTimerThread1 = 0;
    myTimerThread2 = 0;
    startTimer(40);

    connect(mySetButton, SIGNAL(clicked()), this, SLOT(onSetPressed()));
    connect(myStopButton, SIGNAL(clicked()), this, SLOT(onStopPressed()));
}

void Dialog::timerEvent(QTimerEvent *) {
    int timer;
    myMutex1.lock();
    timer = myTimer1;
    myMutex1.unlock();
    myLabel1->setText(QString("<b>Timer 1:</b> %1").arg(timer));

    myMutex2.lock();
    timer = myTimer2;
    myMutex2.unlock();
    myLabel2->setText(QString("<b>Timer 2:</b> %1").arg(timer));
}

void Dialog::onSetPressed() {
    if (mySetLineEdit->text() == "") {
        return;
    }
    int interval = mySetLineEdit->text().toInt();
    if (myComboBox->currentIndex() == 0) {
        if (myTimerThread1 != 0) {
            myTimerThread1->terminate();
            myTimerThread1->wait();
            delete myTimerThread1;
            myTimerThread1 = 0;
        }
        myTimerThread1 = new Timer(&myTimer1, &myMutex1, interval, this);
        myTimerThread1->start();
    } else {
        if (myTimerThread2 != 0) {
            myTimerThread2->terminate();
            myTimerThread2->wait();
            delete myTimerThread1;
            myTimerThread2 = 0;
        }
        myTimerThread2 = new Timer(&myTimer2, &myMutex2, interval, this);
        myTimerThread2->start();
    }
}

void Dialog::onStopPressed() {
    if (myComboBox->currentIndex() == 0) {
        if (myTimerThread1 != 0) {
            myTimerThread1->terminate();
            myTimerThread1->wait();
            delete myTimerThread1;
            myTimerThread1 = 0;
        }
    } else {
        if (myTimerThread2 != 0) {
            myTimerThread2->terminate();
            myTimerThread2->wait();
            delete myTimerThread2;
            myTimerThread2 = 0;
        }
    }
}
