#ifndef BALLWIDGET_H
#define BALLWIDGET_H

#include <QTimerEvent>
#include <QPoint>
#include <QRect>
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <QTimer>
#include <QColor>
#include <QFont>
#include <QTime>


class BallWidget: public QWidget{
  Q_OBJECT;
  int myvx;
  int myvy;
  int myx;
  int myy;
  int myg;
  int myradius;
  QColor* mycolor;
  QColor* mybackcolor;
  QTimer* mytimer;
  
  public:
  BallWidget(QWidget* parent = NULL);
  
  void paintEvent(QPaintEvent* e);
  public slots:
  void move();
};

#endif
