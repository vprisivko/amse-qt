#include "ballwidget.h"

#include <algorithm>

#include <QtGui/QPainter>
#include <QtCore/QTimer>
#include <QtCore/QtGlobal>
#include <QKeyEvent>

#include <cmath>

BallWidget::BallWidget(int ballArea, int updateInterval, const QColor& ballColor, const QColor& backColor, QWidget *parent, Qt::WFlags flags) : QWidget(parent, flags),  myUpdateInterval(updateInterval), myBallArea(ballArea), myBallColor(ballColor), myBackgroundColor(backColor)
{
  setWindowTitle("Press Space to change direction");
  myVerticalRadius = myHorizontalRadius = sqrt((qreal)ballArea);
  //minimal area for ball to fit in
  setMinimumSize(QSize(3 * myHorizontalRadius, 3 * myVerticalRadius));
  myBallPos = QPoint(width() / 2, height() / 2);
  myBallVelocity.setX((qreal) (qrand() % 500));
  myBallVelocity.setY((qreal) (qrand() % 500));
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
  if ((myBallPos.x() + myHorizontalRadius + dx > width()))
  {
    myHorizontalRadius = qMax((qreal)(sqrt((qreal)myBallArea / 2)), width() - myBallPos.x() - dx);
    myVerticalRadius = myBallArea / myHorizontalRadius;
  }

  if ((myBallPos.x() - myHorizontalRadius + dx < 0))
  {
    myHorizontalRadius = qMax((qreal)(sqrt((qreal)myBallArea / 2)), myBallPos.x() + dx);
    myVerticalRadius = myBallArea / myHorizontalRadius;
  }

  if ((myBallPos.y() + myVerticalRadius + dy > height()))
  {
    myVerticalRadius = qMax((qreal)(sqrt((qreal)myBallArea / 2)), height() - myBallPos.y() - dy);
    myHorizontalRadius = myBallArea / myVerticalRadius;
  }

  if ((myBallPos.y() - myVerticalRadius + dy < 0))
  {
    myVerticalRadius = qMax((qreal)(sqrt((qreal)myBallArea / 2)), myBallPos.y() + dy);
    myHorizontalRadius = myBallArea / myVerticalRadius;
  }

  //reverse the speed
  if (((myBallPos.x() + myHorizontalRadius + dx > width() + 0.1f) && (myBallVelocity.x() > 0)) || ((myBallPos.x() - myHorizontalRadius + dx < -0.1f) && (myBallVelocity.x() < 0)))
  {
    myBallVelocity.rx() *= -1;
    dx = -dx;
  }

  if (((myBallPos.y() + myVerticalRadius + dy > height() + 0.1f) && (myBallVelocity.y() > 0)) || ((myBallPos.y() - myVerticalRadius + dy < -0.1f) && (myBallVelocity.y() < 0)))
  {
    myBallVelocity.ry() *= -1;
    dy = -dy;
  }

  myBallPos.rx() += dx;
  myBallPos.ry() += dy;

  //restore ball size
  if ((myBallPos.y() + myVerticalRadius < height()) && (myBallPos.y() - myVerticalRadius  > 0) && (myHorizontalRadius > myVerticalRadius))
  {
    myVerticalRadius = qMin((qreal)(sqrt((qreal)myBallArea)), height() - myBallPos.y());
    myVerticalRadius = qMin(myVerticalRadius, myBallPos.y());
    myHorizontalRadius = myBallArea / myVerticalRadius;
  }

  if ((myBallPos.x() + myHorizontalRadius < width()) && (myBallPos.x() - myHorizontalRadius  > 0) && (myVerticalRadius > myHorizontalRadius))
  {
    myHorizontalRadius = qMin((qreal)(sqrt((qreal)myBallArea)), width() - myBallPos.x());
    myHorizontalRadius = qMin(myHorizontalRadius, myBallPos.x());
    myVerticalRadius = myBallArea / myHorizontalRadius;
  }

  update();

}

void BallWidget::keyPressEvent(QKeyEvent* e)
{
  if (e->key() == Qt::Key_Space)
  {
    myBallVelocity.setX((qreal) (qrand() % 500));
    myBallVelocity.setY((qreal) (qrand() % 500));
  }
}

void BallWidget::resizeEvent(QResizeEvent*)
{
  if (myBallPos.x() + myHorizontalRadius > width())
  {
    myBallPos.rx() = width() - myHorizontalRadius;
  }
  if (myBallPos.y() + myVerticalRadius > height())
  {
    myBallPos.ry() = height() - myVerticalRadius;
  }

}
