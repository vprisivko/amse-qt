#ifndef _BALL_
#define _BALL_

#include <QPainter>
#include <QDialog>
#include <QTimerEvent>
#include <QWidget>
#include <QPoint>

class ball : public QDialog{
  Q_OBJECT;
  
  public:
    ball (QWidget* parent = 0);
    virtual void timerEvent (QTimerEvent* e);
    virtual void paintEvent (QPaintEvent* e);
    
  private:
    int radius;
    int x_radius;
    int y_radius;
    int dx, dy;
    QPoint center;
    
};
    
    

#endif
