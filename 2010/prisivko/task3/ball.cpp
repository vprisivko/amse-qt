#include <QDebug>
#include "ball.h"

BallDialog::BallDialog(int radius, int XVelocity, int YVelocity)
{
  myRadius = radius;
  myXRadius = radius;
  myYRadius = radius;
  myXCompression = 0;
  myYCompression = 0;
  myXVelocity = XVelocity;
  myYVelocity = YVelocity;
  myX = 0;
  myY = 0;
  myXIncrement = (float)(myXVelocity * TIMER_INTERVAL) / 60;
  myYIncrement = (float)(myYVelocity * TIMER_INTERVAL) / 60;

  myPainter = new QPainter();
  myTimer = new QTimer(this);

  connect(myTimer, SIGNAL(timeout()), this, SLOT(timeEvent()));
  myTimer->start(TIMER_INTERVAL);
}

void BallDialog::paintEvent(QPaintEvent *) 
{
  myPainter->begin(this);
  myPainter->setBrush(Qt::SolidPattern);
  
  int x1, y1, x2, y2;
  
  this->geometry().getCoords(&x1, &y1, &x2, &y2);
  myPainter->drawEllipse(QPoint(myX + (x2 - x1) * 0.5, myY + (y2 - y1) * 0.5), myXRadius, myYRadius);
  myPainter->end();
}

void BallDialog::timeEvent() 
{
  if (myXCompression == 0 && myYCompression == 0) 
  {
    if ((myX + myXRadius + myXIncrement) >= this->width() / 2  || (myX - myXRadius + myXIncrement) <= -this->width() / 2) 
    {
      myXCompression = 1;
    }
    else if ((myY + myYRadius + myYIncrement) >= this->height() / 2 || (myY - myYRadius + myYIncrement) <= -this->height() / 2) 
    {
      myYCompression = 1;
    }
    else
    {
      myX += myXIncrement;
      myY += myYIncrement;
    }
  }
  else 
  {
    Axis ax = myXCompression != 0 ? X : Y;

    press(ax);

    myX += myXIncrement;
    myY += myYIncrement;
  }

  repaint();
}

void BallDialog::press(Axis axis) 
{
  if (axis == X)
  {
    if (myXCompression == 1 && myXRadius > myRadius / 2) 
    {
      myXRadius -= abs(myXIncrement);
    }
    else if (myXCompression == 1 && myXRadius <= myRadius / 2) 
    {
      myXCompression = -1;
      myXIncrement = -myXIncrement;
    }
    else if (myXCompression == -1 && myXRadius < myRadius) 
    {
      myXRadius += abs(myXIncrement);
    }
    else 
    {
      myXCompression = 0;
    }
  }
  else
  {
    if (myYCompression == 1 && myYRadius > myRadius / 2) 
    {
      myYRadius -= abs(myYIncrement);
    }
    else if (myYCompression == 1 && myYRadius <= myRadius / 2) 
    {
      myYCompression = -1;
      myYIncrement = -myYIncrement;
    }
    else if (myYCompression == -1 && myYRadius < myRadius) 
    {
      myYRadius += abs(myYIncrement);
    }
    else 
    {
      myYCompression = 0;
    }
  }
}
