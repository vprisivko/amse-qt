#include <QVBoxLayout>
#include <QHBoxLayout>

#include "src.h"

myDialog::myDialog(QWidget *p):QDialog(p){
    QVBoxLayout* layout = new QVBoxLayout;
    setLayout(layout);

    QHBoxLayout* l1 = new QHBoxLayout;
    lbl1 = new QLabel("Timer 1");
    lbltimer1 = new QLabel("");
    l1->addWidget(lbl1);
    l1->addWidget(lbltimer1);

    QHBoxLayout* l2 = new QHBoxLayout;
    lbl2 = new QLabel("Timer 2");
    lbltimer2 = new QLabel("");
    l2->addWidget(lbl2);
    l2->addWidget(lbltimer2);

    cbChoose = new QComboBox;    
    cbChoose->addItem("timer 1");
    cbChoose->addItem("timer 2");

    QHBoxLayout* l = new QHBoxLayout;
    leInt = new QLineEdit;
    btnSet = new QPushButton("Set");
    l->addWidget(leInt);
    l->addWidget(btnSet);

    btnStop = new QPushButton("Stop");

    layout->insertLayout(-1, l1);
    layout->insertLayout(-1, l2);
    layout->addWidget(cbChoose);
    layout->insertLayout(-1, l);
    layout->addWidget(btnStop);

    connect(btnSet, SIGNAL(clicked()), this, SLOT(set()));
    connect(btnStop, SIGNAL(clicked()), this, SLOT(stop()));

    count1 = count2 = 0;
    isTimerOn1 = isTimerOn2 = false;

}

void myDialog::set(){
    int currentTimer = cbChoose->currentIndex();
    int interval = leInt->text().toInt();

    if (currentTimer == 0){
        if(isTimerOn1) killTimer(timer_id1);
        timer_id1 = startTimer(interval);
        isTimerOn1 = true;
        emit isSet();
    } else {
        if(isTimerOn2) killTimer(timer_id2);
        timer_id2 = startTimer(interval);
        isTimerOn2 = true;
        emit isSet();
    }

}

void myDialog::stop(){
    int currentTimer = cbChoose->currentIndex();

    if((currentTimer == 0) && isTimerOn1){
        killTimer(timer_id1);
        isTimerOn1 = false;
        emit isStop();
    }
    if((currentTimer == 1) && isTimerOn2){
        killTimer(timer_id2);
        isTimerOn2 = false;
        emit isStop();
    }

}

void myDialog::timerEvent(QTimerEvent *e){
    int currentTId = e->timerId();

    if(isTimerOn1 && (timer_id1 == currentTId)){
        count1 ++;
        lbltimer1->setText(QString::number(count1));
    }

    if(isTimerOn2 && (timer_id2 == currentTId)){
        count2 ++;
        lbltimer2->setText(QString::number(count2));
    }
}
