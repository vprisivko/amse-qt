#ifndef _BALL_
#define _BALL_

#include <QWidget>
#include <QEvent>
#include <QPaintEvent>
#include <QTimer>
#include <QPushButton>
#include <QResizeEvent>
#include <QPoint>
#include "Racket.h"
class Game;
class Ball: public QWidget {
  Q_OBJECT;

  public:
     Ball( int radius = 0, int x = 0, int y = 0, QWidget* parent = 0);

     void paintEvent(QPaintEvent *);
     void resizeEvent(QResizeEvent *);
     void timerEvent(QTimerEvent *);

  public slots:
     void start();
     void left();
     void right();

  public: signals:
     void Start();
     void gameover();
     void noleft();
     void noright();
     void everything();


  private:
    friend class Game;
    int mytimer;
     int radius; 
    int x_radius;
    int y_radius;
    int dx, dy;
    QPoint center;
    int myHeight, myWidth;
    Racket myRacket;

};

#endif 

