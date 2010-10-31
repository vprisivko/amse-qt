#include "Ball.h"

Ball::Ball(){
  x = 320;
  y = 240;
  radius= 10;
  vx = 0;
  vy = 1;
  color = new QColor(Qt::yellow);
}

QDomElement Ball::serialize(QDomDocument& doc){
  QDomElement el = doc.createElement("ball");
  el.setAttribute("x",QString::number(x));
  el.setAttribute("y",QString::number(y));
  return el;
}
