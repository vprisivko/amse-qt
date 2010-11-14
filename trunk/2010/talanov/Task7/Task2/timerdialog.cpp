#include "timerdialog.h"

#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QComboBox>
#include <QtCore/QString>
#include <QtGui/QPushButton>
#include <QtGui/QLineEdit>
#include <QtCore/QTimerEvent>


TimerDialog::TimerDialog(QWidget *parent, Qt::WFlags flags)
    : QDialog(parent, flags)
{

  myActiveTimerIndex = 0;
  myTimerId1 = 0;
  myTimerId2 = 0;
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
  combo->setObjectName("comboBox");
  combo->addItem(timerName1);
  combo->addItem(timerName2);
  QObject::connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(setActiveTimer(int)));

  mainLayout->addWidget(combo);

  QHBoxLayout* layout1 = new QHBoxLayout;

  QPushButton* setButton = new QPushButton("set", this);
  setButton->setObjectName("setButton");
  QObject::connect(setButton, SIGNAL(clicked()), this, SLOT(resetActiveTimer()));
  layout1->addWidget(setButton);
  QLineEdit* lineEdit = new QLineEdit(QString::number(myCurrentInterval), this);
  QObject::connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(setCurrentInterval(const QString&)));
  layout1->addWidget(lineEdit);

  mainLayout->addItem(layout1);

  QPushButton* stopButton = new QPushButton("stop", this);
  stopButton->setObjectName("stopButton");
  QObject::connect(stopButton, SIGNAL(clicked()), this, SLOT(stopActiveTimer()));
  mainLayout->addWidget(stopButton);

  setLayout(mainLayout);
}

TimerDialog::~TimerDialog()
{

}

void TimerDialog::resetActiveTimer()
{
  if (myActiveTimerIndex == 0) 
  {
    if (myTimerId1)
    {
      killTimer(myTimerId1);
    }
    myTimerId1 = startTimer(myCurrentInterval);
  }
  else
  {
    if (myTimerId2)
    {
      killTimer(myTimerId2);
    }
    myTimerId2 = startTimer(myCurrentInterval);
    
  }    
}

void TimerDialog::stopActiveTimer()
{
  if (myActiveTimerIndex == 0) 
  {
    if (myTimerId1)
    {
      killTimer(myTimerId1);
    }
  }
  else
  {
    if (myTimerId2)
    {
      killTimer(myTimerId2);
    }
  }    
}

void TimerDialog::setActiveTimer(int timerIndex)
{
  myActiveTimerIndex = timerIndex;
}

void TimerDialog::increaseCount(QLabel* countLabel)
{
  countLabel->setText(QString::number(countLabel->text().toInt() + 1));
}

void TimerDialog::timerEvent(QTimerEvent* e)
{
  if (e->timerId() == myTimerId1)
  {
    increaseCount(myCountLabel1);
  }
  else
  {
    increaseCount(myCountLabel2);
  }
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