#include "MyDialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

MyDialog::MyDialog(QWidget *parent, Qt::WFlags flags) : QDialog(parent, flags)
{
  currentTime1 = 0;
  currentTime2 = 0;
  currentTimerNumber = 0;
  timer1Interval = 0;
  timer2Interval = 0;

  QVBoxLayout *vboxLayout = new QVBoxLayout();
  
  setLayout(vboxLayout);

  QHBoxLayout *timer1Layout = new QHBoxLayout();

  layout()->addItem(timer1Layout);

  QLabel *timer1Label = new QLabel("<b>Timer1</b>", this);
  timer1LCD = new QLCDNumber(this);

  timer1Layout->addWidget(timer1Label);
  timer1Layout->addWidget(timer1LCD);
  
  QHBoxLayout *timer2Layout = new QHBoxLayout();
 
  layout()->addItem(timer2Layout);

  QLabel *timer2Label = new QLabel("<b>Timer2</b>", this);
  timer2LCD = new QLCDNumber(this);

  timer2Layout->addWidget(timer2Label);
  timer2Layout->addWidget(timer2LCD);

  timersComboBox = new QComboBox(this);
  timersComboBox->addItem("Timer1");
  timersComboBox->addItem("Timer2");

  layout()->addWidget(timersComboBox);

  QHBoxLayout *intervalLayout = new QHBoxLayout();

  layout()->addItem(intervalLayout);

  intervalLineEdit = new QLineEdit("1000", this);
  QPushButton *intervalSetButton = new QPushButton("Set", this);

  intervalLayout->addWidget(intervalLineEdit);
  intervalLayout->addWidget(intervalSetButton);

  QPushButton *stopButton = new QPushButton("Stop", this);

  layout()->addWidget(stopButton);

  connect(intervalSetButton, SIGNAL(pressed()), this, SLOT(setInterval()));
  connect(stopButton, SIGNAL(pressed()), this, SLOT(stopTimer()));
  connect(timersComboBox, SIGNAL(activated(int)), this, SLOT(changeCurrentTimer()));
}

void MyDialog::setInterval()
{
  int interval = intervalLineEdit->text().toInt();

  if (currentTimerNumber == 0)
  {
    killTimer(timer_id);
    timer_id = startTimer(interval);

    timer1Interval = interval;
  }
  else
  {
    killTimer(timer_e);
    timer_e = startTimer(interval);

    timer2Interval = interval;
  }
}

void MyDialog::stopTimer()
{
  if (currentTimerNumber == 0)
  {
    killTimer(timer_id);
  }
  else
  {
    killTimer(timer_e);
  }
}

void MyDialog::changeCurrentTimer()
{
  currentTimerNumber = timersComboBox->currentIndex();
}

void MyDialog::timerEvent(QTimerEvent *e)
{
  if (e->timerId() == timer_id)
  {
    currentTime1 += timer1Interval;
    
    timer1LCD->display(currentTime1);
  }
  else
  {
    currentTime2 += timer2Interval;
    
    timer2LCD->display(currentTime2);
  }
}