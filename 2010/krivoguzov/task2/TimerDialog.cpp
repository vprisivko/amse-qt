#include <TimerDialog.h>
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

    number1 = new QLCDNumber;
    number2 = new QLCDNumber;
    number1->setAutoFillBackground(true);
    number2->setAutoFillBackground(true);
    QPalette pal = number1->palette();
    pal.setColor(QPalette::Normal, QPalette::Window, QColor(0,49,83));
    number1->setPalette(pal);
    number2->setPalette(pal);

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
        number1->display(number1->value()+1);
    else if(event->timerId()==myTimerId2)
        number2->display(number2->value()+1);
}
