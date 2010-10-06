#ifndef TABLE_H
#define TABLE_H

#include <QDialog>
#include <QPaintEvent>
#include <QTimerEvent>

class Table: public QDialog {
Q_OBJECT;

public:
  Table(QWidget *w = 0);

private:
  struct Ball {
    int x, y, rx, ry, rxeff, ryeff, dx, dy;
    void move(int, int);
  };
  Ball b;


protected:
  virtual void paintEvent(QPaintEvent*);
  virtual void timerEvent(QTimerEvent*);



};

#endif
