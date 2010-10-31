#ifndef RACKET_H
#define RACKET_H

#include <QColor>
#include <QDomDocument>
#include <QDomElement>

struct Racket{
  int x;
  int halfwidth;
  int height;
  int step;
  QColor* color;
  QDomElement serialize(QDomDocument& doc);
  Racket();
};

#endif
