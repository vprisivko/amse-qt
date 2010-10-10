#include "ball.h"
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <QColor>
#include <QPen>


ball::ball( QWidget* parent) : QDialog( parent){
  srand ( time(NULL) );
  if (width() < height()){
    x_radius = rand() % (width()/10-10) + 10;
  }
  else{
    x_radius = rand() % (height()/10-10) + 10;
  }
  y_radius = x_radius;
  radius = y_radius;
  center = QPoint (width()/2,height()/2);
  dx = dy = 0;
  while ((dx == 0)&&(dy == 0)){
    dx = rand() % 10;
    dy = rand() % 10;
  }
  startTimer(10);
}

void ball::paintEvent (QPaintEvent*){
  QPainter p ( this );
  p.setPen(Qt::NoPen);
  p.setBrush( QBrush( QColor(218,112,214) ) );
  p.drawEllipse( center, x_radius, y_radius);
}

void ball::timerEvent (QTimerEvent*){
  int w = width();
  int h = height();
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
  
  if ( y + radius > h){
    y1 = h - y;
  }
  
  if ( y - radius < 0){
    y1 = y;
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
  
  update();
  
} 
   
    
  
  
  
    


