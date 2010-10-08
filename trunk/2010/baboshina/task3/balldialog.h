#ifndef _MOVINGBALL_H_
#define _MOVINGBALL_H_

#include <QDialog>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QWidget>

class ballDialog : public QDialog{
Q_OBJECT

public:
  ballDialog(QWidget* p = NULL);

  virtual void paintEvent(QPaintEvent*);
  virtual void timerEvent(QTimerEvent*);

private:
  struct ball{
      int x, y, r, rx, ry, dx, dy;
      void move(int, int);
  } b;

  int timer_id;

};

#endif
