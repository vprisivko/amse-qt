#include "timerdialog.h"

#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QComboBox>
#include <QtCore/QString>
#include <QtGui/QPushButton>
#include <QtGui/QLineEdit>
#include <QtCore/QTimerEvent>
#include <QtCore/QMutexLocker>
#include <QtCore/QThread>


TimerDialog::TimerDialog(QWidget *parent, Qt::WFlags flags)
    : QDialog(parent, flags), myTimer1(myCounter1, myCounterMutex1, this),
    myTimer2(myCounter2, myCounterMutex2, this)
{

    myActiveTimerIndex = 0;

    myCounter1 = 0;
    myCounter2 = 0;
    myCurrentInterval = 1000;

    QString timerName1 = "Timer 1";
    QString timerName2 = "Timer 2";

    QVBoxLayout* mainLayout = new QVBoxLayout;

    QHBoxLayout* labelLayout1 = new QHBoxLayout;
    labelLayout1->addWidget(new QLabel(timerName1, this));
    myCountLabel1 = new QLabel("0", this);
    labelLayout1->addWidget(myCountLabel1);
    mainLayout->addItem(labelLayout1);


    QHBoxLayout* labelLayout2 = new QHBoxLayout;
    labelLayout2->addWidget(new QLabel(timerName2, this));
    myCountLabel2 = new QLabel("0", this);
    labelLayout2->addWidget(myCountLabel2);
    mainLayout->addItem(labelLayout2);

    QComboBox* combo = new QComboBox(this);
    combo->addItem(timerName1);
    combo->addItem(timerName2);
    QObject::connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(setActiveTimer(int)));

    mainLayout->addWidget(combo);

    QHBoxLayout* layout1 = new QHBoxLayout;

    QPushButton* setButton = new QPushButton("set", this);
    QObject::connect(setButton, SIGNAL(clicked()), this, SLOT(resetActiveTimer()));
    layout1->addWidget(setButton);
    QLineEdit* lineEdit = new QLineEdit(QString::number(myCurrentInterval), this);
    QObject::connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(setCurrentInterval(const QString&)));
    layout1->addWidget(lineEdit);

    mainLayout->addItem(layout1);

    QPushButton* stopButton = new QPushButton("stop", this);
    QObject::connect(stopButton, SIGNAL(clicked()), this, SLOT(stopActiveTimer()));
    mainLayout->addWidget(stopButton);

    //timer for updates
    startTimer(100);

    setLayout(mainLayout);

    myTimer1.start();
    myTimer2.start();
}

TimerDialog::~TimerDialog()
{

}

void TimerDialog::resetActiveTimer()
{
    if (myActiveTimerIndex == 0)
    {
        myTimer1.setInterval(myCurrentInterval);
        myTimer1.setIsRunning(true);
    }
    else
    {
        myTimer2.setInterval(myCurrentInterval);
        myTimer2.setIsRunning(true);
    }
}

void TimerDialog::stopActiveTimer()
{
    if (myActiveTimerIndex == 0)
    {
        myTimer1.setIsRunning(false);
    }
    else
    {
        myTimer2.setIsRunning(false);
    }
}

void TimerDialog::setActiveTimer(int timerIndex)
{
    myActiveTimerIndex = timerIndex;
}

void TimerDialog::refreshLabels()
{
    //suppose we use this counters here
    QMutexLocker locker1(&myCounterMutex1);
    myCountLabel1->setText(QString::number(myCounter1));
    locker1.unlock();

    QMutexLocker locker2(&myCounterMutex2);
    myCountLabel2->setText(QString::number(myCounter2));
    locker2.unlock();
}

void TimerDialog::timerEvent(QTimerEvent*)
{
    refreshLabels();
}

void TimerDialog::setCurrentInterval(const QString& newIntervalText)
{
    bool success;
    int newInterval = newIntervalText.toInt(&success);
    if (success)
    {
        myCurrentInterval = newInterval;
    }
}
