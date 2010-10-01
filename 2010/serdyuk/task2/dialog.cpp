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

    myTimer1Id = 0;
    myTimer2Id = 0;

    connect(mySetButton, SIGNAL(clicked()), this, SLOT(onSetPressed()));
    connect(myStopButton, SIGNAL(clicked()), this, SLOT(onStopPressed()));
}

void Dialog::timerEvent(QTimerEvent *e) {
    if (e->timerId() == myTimer1Id) {
        myTimer1 += 1;
        myLabel1->setText(QString("<b>Timer 1:</b> %1").arg(myTimer1));
    } else {
        myTimer2 += 1;
        myLabel2->setText(QString("<b>Timer 2:</b> %1").arg(myTimer2));
    }
}

void Dialog::onSetPressed() {
    if (mySetLineEdit->text() == "") {
        return;
    }
    int interval = mySetLineEdit->text().toInt();
    if (myComboBox->currentIndex() == 0) {
        if (myTimer1Id != 0) {
            killTimer(myTimer1Id);
        }
        myTimer1Id = startTimer(interval);
    } else {
        if (myTimer2Id != 0) {
            killTimer(myTimer2Id);
        }
        myTimer2Id = startTimer(interval);
    }
}

void Dialog::onStopPressed() {
    if (myComboBox->currentIndex() == 0) {
        if (myTimer1Id != 0) {
            killTimer(myTimer1Id);
            myTimer1Id = 0;
        }
    } else {
        if (myTimer2Id != 0) {
            killTimer(myTimer2Id);
            myTimer2Id = 0;
        }
    }
}
