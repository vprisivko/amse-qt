#ifndef BALLWIDGET_H
#define BALLWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QPaintEvent>
#include <QtCore/QTimer>
#include <QtCore/QPoint>
#include <QtGui/QColor>
#include <QtGui/QKeyEvent>
#include <QtGui/QResizeEvent>


class BallWidget : public QWidget
{
   Q_OBJECT

public:
  BallWidget(int ballArea, int updateIntercal, const QColor& ballColor, const QColor& backColor, QWidget *parent = 0, Qt::WFlags flags = 0);
  ~BallWidget();

protected:

  void keyPressEvent(QKeyEvent*);
  void paintEvent(QPaintEvent*);
  void resizeEvent(QResizeEvent*);

protected slots:

  void move();

private:

  const int myUpdateInterval;
  const int myBallArea;

  const QColor myBallColor;
  const QColor myBackgroundColor;

  QPointF myBallPos;
  QPointF myBallVelocity;

  qreal myVerticalRadius;
  qreal myHorizontalRadius;

};

#endif // BALLWIDGET_H
