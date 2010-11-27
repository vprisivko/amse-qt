#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QIntValidator>

#include "dialog.h"
#include "timer.h"


Dialog::Dialog(QWidget *parent): QDialog(parent), REFRESH_TIME(100) {

    // create interface
    
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* lay = 0;
    setLayout(mainLayout);
    
    lblTimer[0] = new QLabel("<b>Timer #1</b>");
    lblTimer[1] = new QLabel("<b>Timer #2</b>");
    
    mainLayout->addWidget( lblTimer[0] );
    mainLayout->addWidget( lblTimer[1] );
   
    cbChooseTimer = new QComboBox();
    cbChooseTimer->addItem("Timer 1");
    cbChooseTimer->addItem("Timer 2");
    mainLayout->addWidget( cbChooseTimer );

    lay = new QHBoxLayout();
    leInterval = new QLineEdit("enter interval in ms");
    leInterval->setValidator( new  QIntValidator() );
    btnSet = new QPushButton("set");
    lay->addWidget( leInterval );
    lay->addWidget( btnSet );
    mainLayout->addLayout(lay);

    btnStop = new QPushButton("Stop!");
    mainLayout->addWidget(btnStop);
    

    createConnects();

    // class fields initialization
    countTimer[0] = countTimer[1] = 0;

    startTimer(REFRESH_TIME);


}

Dialog::~Dialog() {
    timers[0].terminate();
    timers[1].terminate();

}

void Dialog::createConnects() {
    connect( btnSet, SIGNAL(clicked()), this, SLOT(setTimer()) );
    connect( btnStop, SIGNAL(clicked()), this, SLOT(stopTimer()) );
    connect( this, SIGNAL(signalStopTimer(Timer*)), &timers[0], SLOT(stop(Timer*) ) );
    connect( this, SIGNAL(signalStopTimer(Timer*)), &timers[1], SLOT(stop(Timer*) ) );
}


void Dialog::stopTimer() {

    int currentTimer = cbChooseTimer->currentIndex();

    if ( timers[currentTimer].isRunning() == false) {
        QMessageBox( QMessageBox::Warning, "Sorry", "You haven't set this timer!", QMessageBox::Ok).exec();
        return;
    }

    emit signalStopTimer(&timers[currentTimer]); //timers[currentTimer].stop();
}

void Dialog::setTimer() {

    bool ok;
    int interval = leInterval->text().toInt(&ok);
    
    if (ok == false) {
         QMessageBox( QMessageBox::Warning, "Sorry", "You should enter only digits!!!", QMessageBox::Ok).exec();
        return;
    }
    
    int currentTimer = cbChooseTimer->currentIndex();  

    timers[currentTimer].setParameters(&countTimer[currentTimer], interval, &mutexes[currentTimer]);
    timers[currentTimer].start();

}

void Dialog::timerEvent(QTimerEvent*) {

    for(int numberTimer=0; numberTimer < 2; ++numberTimer) {
        mutexes[numberTimer].lock();
        QString str = QString("<b>Timer #%1: %2</b>").arg(numberTimer+1).arg( countTimer[numberTimer] );
        mutexes[numberTimer].unlock();
        lblTimer[numberTimer]->setText( str );

    }
    
}
