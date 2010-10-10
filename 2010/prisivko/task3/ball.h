#ifndef _BALL_H_
#define _BALL_H_

#include <QPushButton>
#include <QDialog>
#include <QPainter>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QTimer>

class BallDialog: public QDialog {
 
  Q_OBJECT;

private:

  enum Axis
  {
    X,
    Y
  };

public:
  BallDialog(int radius = 35, int XVelocity = 10, int YVelocity = 10);
  void paintEvent(QPaintEvent *);
  void press(Axis axis);

public slots:
  void timeEvent();

private:
  int myXRadius;
  int myYRadius;
  int myRadius;
  float myX;
  float myY;
  int myXVelocity, myYVelocity;
  float myXIncrement, myYIncrement;
  QPainter *myPainter;
  QTimer *myTimer;
  int myXCompression, myYCompression; 

  static const int TIMER_INTERVAL = 10;
};

#endif // _BALL_H_
