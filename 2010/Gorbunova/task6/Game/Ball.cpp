#include <QPainter>
#include <QColor>
#include <Qt>
#include <QRect>
#include <QPoint>
#include <algorithm>
#include "Ball.h"

Ball::Ball( int radius1, int directionX, int directionY,QWidget *parent): QWidget(parent){
  center = QPoint(100, 100);
  radius = radius1;
  y_radius = radius;
  x_radius = radius;
  dx = directionX;
  dy = directionY;
  myHeight= 0;
  myWidth = 0;
  myRacket.length = radius * 3;
  this->setMinimumHeight(radius * 10);
  this->setMinimumWidth(radius * 10);
}

void Ball::timerEvent(QTimerEvent *e) {
 if (e->timerId() == mytimer) {
    int w = width();
    int x = center.x();
    int y = center.y();
  
    x += dx;
    y += dy;
   
   
    int x1 = radius;
    int y1 = radius;
  
    if ( x+ radius > w){
      x1 = w - x;
    }
  
    if ( x - radius < 0){
      x1 = x;
    }
  
    
    if ( y - radius < 0){
      y1 = y;
    }
  
   
    
    if ( y + radius > myRacket.yTopLeft){
      if ( (x > myRacket.xTopLeft) && ( x< myRacket.xTopLeft + myRacket.length)){
         
        y1 = myRacket.yTopLeft - y;
      } 
      else{
        emit gameover();
        killTimer(mytimer);
        center = QPoint(100,100);
        radius = 30;
        y_radius = radius;
        x_radius = radius;
      }
    }
    
    if ( y1 < radius/2){
      dy = -dy;
    }
  
    if ( x1 < radius/2){
      dx= -dx;
    }
    center = QPoint(x,y);
    x_radius = x1;
    y_radius = y1;
  
   
    repaint();
    }
}

void Ball::left() {
 myRacket.xTopLeft -= 20;

 if (myRacket.xTopLeft < 0)
   emit noleft();
 repaint();
}

void Ball::right() {
  myRacket.xTopLeft += 20;
  if (myRacket.xTopLeft + myRacket.length > myWidth)
    emit noright();
  repaint();
}

void Ball::start() {
   
  mytimer = startTimer(20);
  center = QPoint(100,100);
  dx = 1;
  radius = 30;
  y_radius = radius;
  x_radius = radius;
  myRacket.yTopLeft = height() - 5;
  myRacket.xTopLeft = center.x()-50;
  myHeight = width();
  myWidth = height();
  emit Start();
        
}

void Ball::resizeEvent(QResizeEvent *e) {
  myRacket.yTopLeft = e->size().height() - 5;
  repaint();
}

void Ball::paintEvent(QPaintEvent *) {
  
  QPainter p ( this );
   p.setBrush( QBrush( QColor(218,112,214) ) );
  p.drawRect(myRacket.xTopLeft, myRacket.yTopLeft, myRacket.length, 5);
  p.setPen(Qt::NoPen);
  p.setBrush( QBrush( QColor(218,112,214) ) );
  p.drawEllipse( center, x_radius, y_radius);
  
 
  
}


