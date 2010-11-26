#include "threadedtimers.h"
#include "ui_threadedtimers.h"

ThreadedTimers::ThreadedTimers(QWidget *parent) : QWidget(parent), ui(new Ui::ThreadedTimers){

    ui->setupUi(this);
    timers = new Timer[2];
    mutexes = new QMutex[2];
    counters = new int[2];
    memset(counters, 0, sizeof(int) * 2);

    connect(this, SIGNAL(stopTimer(Timer*)), timers, SLOT(stop(Timer*)));
    connect(this, SIGNAL(stopTimer(Timer*)), timers + 1, SLOT(stop(Timer*)));
    connect( timers, SIGNAL(tick()), this, SLOT(tock()));
    connect( timers + 1, SIGNAL(tick()), this, SLOT(tock()));

}


ThreadedTimers::~ThreadedTimers(){
    timers[0].terminate();
    timers[1].terminate();
    delete ui;
    delete[] mutexes;
    delete[] counters;
}


void ThreadedTimers::set(){

    int index = ui->comboBox->currentIndex();
    timers[index].set( ui->lineEdit->text().toInt(), counters + index, mutexes + index );

}


void ThreadedTimers::tock(){
    if ( sender() == timers ){
        mutexes[0].lock();
        int c = counters[0];
        mutexes[0].unlock();
        ui->labelT0->setText( QString("Timer 0:\t") + QString::number(c));
    }
    if ( sender() == timers + 1 ){
        mutexes[1].lock();
        int c = counters[1];
        mutexes[1].unlock();
        ui->labelT1->setText( QString("Timer 1:\t") + QString::number(c));
    }
}


void ThreadedTimers::stop(){
    emit stopTimer(timers + ui->comboBox->currentIndex());
}
