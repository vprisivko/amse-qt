#include "Racket.h"

Racket::Racket(){
  x = 320;
  halfwidth = 30;
  height = 20;
  step=40;
  color = new QColor(Qt::black);
}

QDomElement Racket::serialize(QDomDocument& doc){
  QDomElement el = doc.createElement("racket");
  el.setAttribute("x",QString::number(x));
  el.setAttribute("halfwidth",QString::number(halfwidth));
  return el;
}
