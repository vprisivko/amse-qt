#ifndef BALL_H
#define BALL_H

#include <QColor>
#include <QDomDocument>
#include <QDomElement>


struct Ball{
  int x,y;
  int vx,vy;
  int radius;
  QColor* color;
  QDomElement serialize(QDomDocument& doc);
  Ball();
};

#endif
