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
#include "Ball.h"
#include "Racket.h"
#include <math.h>


class BallWidget: public QWidget{
  Q_OBJECT;
  private:
  Ball* myball;
  Racket* myracket;

  QColor* mybackcolor;

  int myballscount;
  int myscore;
  public:

  static const int windowheight = 480;
  static const int windowwidth = 640;
  static const int ballspeed = 20;
  static const int ballradius = 10;
  static const int rackethalfwidth =30;
  static const int racketheight = 20; 
  
  public:
  BallWidget(QWidget* parent = NULL);
  
  void paintEvent(QPaintEvent* e);
  void loseball();
  int getBallsCount();
  Ball getBall();
  Racket getRacket();
  void start();
  void stop();
  public slots:
  void moveBall();
  void moveRacketRight();
  void moveRacketLeft();
  signals:
  void gameOver();
};

#endif
