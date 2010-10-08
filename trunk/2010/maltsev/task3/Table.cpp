#include "Table.h"
#include <QPainter>
#include <QColor>
#include <QRect>
#include <QTime>

Table::Table(QWidget *parent): QDialog(parent) {
  b.x = width() / 2;
  b.y = height() / 2;
  b.rx = 20;
  b.ry = 20;
  QTime midnight(0, 0, 0);
  qsrand(midnight.secsTo(QTime::currentTime()));
  b.dx = qrand() % 16 - 8;
  b.dy = qrand() % 16 - 8;
  startTimer(25);
}

void Table::paintEvent(QPaintEvent* pe) {
  QPainter p(this);
  p.setPen(QPen(Qt::NoPen));
  p.setBrush(QBrush(QColor(0,150,0)));
  p.drawRect(pe->rect());
  p.setPen(QPen(Qt::SolidLine));
  p.setBrush(QBrush(QColor(255,255,255)));
  p.drawEllipse(b.x - b.rxeff, b.y - b.ryeff, b.rxeff * 2, b.ryeff * 2);
}

void Table::timerEvent(QTimerEvent*) {
  b.move(width(), height());
  update();
}

void Table::Ball::move(int w, int h) {
  x += dx;
  y += dy;
  rxeff = rx;
  ryeff = ry;
  if (x + rx > w) {
    rxeff = w - x;
    if (x + rx/2 > w && dx > 0) {
      dx = -dx;
    }
  }
  if (x - rx < 0) {
    rxeff = x;
    if (x - rx/2 < 0 && dx < 0) {
      dx = -dx;
    }
  }
  if (y + ry > h) {
    ryeff = h - y;
    if (y + ry/2 > h && dy > 0) {
      dy = -dy;
    }
  }
  if (y - ry < 0) {
    ryeff = y;
    if (y - ry/2 < 0 && dy < 0) {
      dy = -dy;
    }
  }
}
