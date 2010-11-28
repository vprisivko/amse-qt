#include "TimerDialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimerEvent>
#include <QPalette>

TimerDialog::TimerDialog(QDialog *parent):QDialog(parent),myTimerId(0), counter1(0), counter2(0){
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
    mutex = new QMutex();
    firstThread = secondThread = 0;
    myTimerId = startTimer(20);
}

void TimerDialog::setPressed(){
    if(intervalEdit->text()!=""){
        switch(myBox->currentIndex()){
            case 0:

                if(!firstThread)
                    firstThread = new IntervalThread(this);

                firstThread->setParams(intervalEdit->text().toInt(), counter1, mutex);

                if(!firstThread->isRunning())
                    firstThread->start();

                break;

            case 1:

                if(!secondThread)
                    secondThread = new IntervalThread(this);

                secondThread->setParams(intervalEdit->text().toInt(), counter2, mutex);

                if(!secondThread->isRunning())
                    secondThread->start();

                break;
        }
    }
}


void TimerDialog::stopPressed(){
    switch(myBox->currentIndex()){
        case 0:
            if(firstThread)
                firstThread->stop();
            break;
        case 1:
            if(secondThread)
                secondThread->stop();
            break;
    }
}

void TimerDialog::timerEvent(QTimerEvent *){

    mutex->lock();
    number1->setText(QString::number(counter1));
    number2->setText(QString::number(counter2));
    mutex->unlock();

}
