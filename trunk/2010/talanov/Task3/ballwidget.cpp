#include "ballwidget.h"

#include <algorithm>

#include <QtGui/QPainter>
#include <QtCore/QTimer>

#include <cmath>

BallWidget::BallWidget(int ballArea, int updateInterval, const QColor& ballColor, const QColor& backColor, QWidget *parent, Qt::WFlags flags) : myBallArea(ballArea), myUpdateInterval(updateInterval), myBallColor(ballColor), myBackgroundColor(backColor)
{
  myBallPos = QPoint(35, 35);
  myVerticalRadius = myHorizontalRadius = sqrt((qreal)ballArea);
  myBallVelocity.setX(-200);
  myBallVelocity.setY(100);
  QTimer* timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(move()));
  timer->start(myUpdateInterval);
}

BallWidget::~BallWidget()
{

}

void BallWidget::paintEvent(QPaintEvent* e)
{
  QPainter p(this);
  p.setBrush(myBackgroundColor);
  p.drawRect(e->rect());
  p.setBrush(myBallColor);
  p.drawEllipse(myBallPos, myHorizontalRadius, myVerticalRadius);
}

void BallWidget::move()
{
  qreal dx = ((qreal)myUpdateInterval * myBallVelocity.x() / (qreal)1000);
  qreal dy = ((qreal)myUpdateInterval * myBallVelocity.y() / (qreal)1000);

  //deform the ball
  if ((myBallPos.x() + myHorizontalRadius + dx > width()) && (myBallVelocity.x() > 0))
  {
    myHorizontalRadius = qMax((qreal)(sqrt((qreal)myBallArea / 2)), width() - myBallPos.x() - dx);
    myVerticalRadius = myBallArea / myHorizontalRadius;
  }

  if ((myBallPos.x() - myHorizontalRadius + dx < 0) && (myBallVelocity.x() < 0))
  {
    myHorizontalRadius = qMax((qreal)(sqrt((qreal)myBallArea / 2)), myBallPos.x() + dx);
    myVerticalRadius = myBallArea / myHorizontalRadius;
  }

  if ((myBallPos.y() + myVerticalRadius + dy > height()) && (myBallVelocity.y() > 0))
  {
    myVerticalRadius = qMax((qreal)(sqrt((qreal)myBallArea / 2)), height() - myBallPos.y() - dy);
    myHorizontalRadius = myBallArea / myVerticalRadius;
  }

  if ((myBallPos.y() - myVerticalRadius + dy < 0) && (myBallVelocity.y() < 0))
  {
    myVerticalRadius = qMax((qreal)(sqrt((qreal)myBallArea / 2)), myBallPos.y() + dy);
    myHorizontalRadius = myBallArea / myVerticalRadius;
  }

  if (((myBallPos.x() + myHorizontalRadius + dx > width()) && (myBallVelocity.x() > 0)) || ((myBallPos.x() - myHorizontalRadius + dx < 0) && (myBallVelocity.x() < 0)))
  {
    myBallVelocity.rx() *= -1;
    dx = -dx;
  }

  if (((myBallPos.y() + myVerticalRadius + dy > height()) && (myBallVelocity.y() > 0)) || ((myBallPos.y() - myVerticalRadius + dy < 0) && (myBallVelocity.y() < 0)))
  {
    myBallVelocity.ry() *= -1;
    dy = -dy;
  }

  myBallPos.rx() += dx;
  myBallPos.ry() += dy;

  //restore ball size
  if ((myBallPos.y() + myVerticalRadius < height()) && (myHorizontalRadius > myVerticalRadius))
  {
    myVerticalRadius = qMin((qreal)(sqrt((qreal)myBallArea)), height() - myBallPos.y());
    myHorizontalRadius = myBallArea / myVerticalRadius;
  }

  if ((myBallPos.y() - myVerticalRadius  > 0) && (myHorizontalRadius > myVerticalRadius))
  {
    myVerticalRadius = qMin((qreal)(sqrt((qreal)myBallArea)), myBallPos.y());
    myHorizontalRadius = myBallArea / myVerticalRadius;
  }

  update();

}