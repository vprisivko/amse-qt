#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QIntValidator>

#include "dialog.h"

Dialog::Dialog(QWidget *parent): QDialog(parent) {

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

    // make connects

    connect( btnSet, SIGNAL(clicked()), this, SLOT(setTimer()) );
    connect( btnStop, SIGNAL(clicked()), this, SLOT(stopTimer()) );


    // class fields initialization

    countTimer[0] = countTimer[1] = 0;
    isTimerOn[0] = isTimerOn[1] = false;


}


void Dialog::stopTimer() {

    int currentTimer = cbChooseTimer->currentIndex();
   
    if ( isTimerOn[currentTimer] == 0) {
        QMessageBox( QMessageBox::Warning, "Sorry", "You haven't set this timer!", QMessageBox::Ok).exec();
        return;
    }
    
    killTimer( timerId[currentTimer] );
    isTimerOn[currentTimer] = false;
    
    lblTimer[currentTimer]->setText(  lblTimer[currentTimer]->text() + " <font color=red>{stopped}</font>" );

}

void Dialog::setTimer() {

    bool ok;
    int interval = leInterval->text().toInt(&ok);
    
    if ( ok == false) {
         QMessageBox( QMessageBox::Warning, "Sorry", "You should enter olny digits!!!", QMessageBox::Ok).exec();
        return;
    }
    
    int currentTimer = cbChooseTimer->currentIndex();  
    
    if (isTimerOn[currentTimer] == true) {
        killTimer( timerId[currentTimer] );
    }
      
    timerId[currentTimer] = startTimer(interval);
    isTimerOn[currentTimer] = true;
    QString str = QString("<b>Timer #%1: %2</b>").arg(currentTimer+1).arg( countTimer[currentTimer] );
    lblTimer[currentTimer]->setText( str );

}

void Dialog::timerEvent(QTimerEvent* e) {
    
    
    int curTimerId = e->timerId();
    int numberTimer;
    
    if (isTimerOn[0] == true && timerId[0] == curTimerId ) {
        numberTimer = 0;
    } else if (isTimerOn[1] == true && timerId[1] == curTimerId ) {
        numberTimer = 1;
    } else {
        qDebug() << "TimerEvent" << "unexpected situation: timer should not be active!"
                 << "unexpected timerId is" << curTimerId;
        return;
    }
   	
    countTimer[numberTimer] += 1;
    
    QString str = QString("<b>Timer #%1: %2</b>").arg(numberTimer+1).arg( countTimer[numberTimer] );
    lblTimer[numberTimer]->setText( str );
    
}
