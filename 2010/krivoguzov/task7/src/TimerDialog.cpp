#include "TimerDialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimerEvent>
#include <QPalette>

TimerDialog::TimerDialog(QDialog *parent):QDialog(parent),myTimerId1(0),myTimerId2(0){
    label1 = new QLabel("Timer1");
    label2 = new QLabel("Timer2");
    setButton = new QPushButton("SET");
    stopButton = new QPushButton("STOP");
    intervalEdit = new QLineEdit;

    myBox = new QComboBox;
    myBox->addItem("Timer1");
    myBox->addItem("Timer2");

    number1 = new QLineEdit;
    number2 = new QLineEdit;
    number1->setText("0");
    number2->setText("0");
    number1->setReadOnly(true);
    number2->setReadOnly(true);
    number1->setAlignment(Qt::AlignRight);
    number2->setAlignment(Qt::AlignRight);

    QHBoxLayout *lay1= new QHBoxLayout();
    lay1->addWidget(label1);
    lay1->addWidget(number1);

    QHBoxLayout *lay2= new QHBoxLayout();
    lay2->addWidget(label2);
    lay2->addWidget(number2);

    QHBoxLayout *editAndSet= new QHBoxLayout();
    editAndSet->addWidget(intervalEdit);
    editAndSet->addWidget(setButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(lay1);
    mainLayout->addLayout(lay2);
    mainLayout->addWidget(myBox);
    mainLayout->addLayout(editAndSet);
    mainLayout->addWidget(stopButton);

    setLayout(mainLayout);

    connect(setButton,SIGNAL(clicked()),this,SLOT(setPressed()));
    connect(stopButton,SIGNAL(clicked()),this,SLOT(stopPressed()));
    setFixedHeight(sizeHint().height());
    setFixedWidth(sizeHint().width());

    intervalEdit->setText("20");
}

void TimerDialog::setPressed(){
    if(intervalEdit->text()!=""){
        switch(myBox->currentIndex()){
            case 0:
                if(!myTimerId1)
                    myTimerId1=startTimer(intervalEdit->text().toInt());
                else{
                    killTimer(myTimerId1);
                    myTimerId1=startTimer(intervalEdit->text().toInt());
                }
                break;
            case 1:
                if(!myTimerId2)
                    myTimerId2=startTimer(intervalEdit->text().toInt());
                else{
                    killTimer(myTimerId2);
                    myTimerId2=startTimer(intervalEdit->text().toInt());
                }
                break;
        }
}
}


void TimerDialog::stopPressed(){
    switch(myBox->currentIndex()){
        case 0:
            if(myTimerId1){
                killTimer(myTimerId1);
                myTimerId1=0;
            }
            break;
        case 1:
            if(myTimerId2){
                killTimer(myTimerId2);
                myTimerId2=0;
            }
            break;
    }
}

void TimerDialog::timerEvent(QTimerEvent *event){
    if(event->timerId()==myTimerId1)
        number1->setText(QString::number(QString(number1->text()).toInt() + 1));
    else if(event->timerId()==myTimerId2)
        number2->setText(QString::number(QString(number2->text()).toInt() + 1));
}
