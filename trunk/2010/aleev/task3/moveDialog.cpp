#include "moveDialog.h"
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <QPen>

moveDialog::moveDialog(QWidget *parent): QDialog(parent){
    //default initialization
    dx = -6;
    dy = 4;
    defRadius = 20;

    ball.radius = QSize(defRadius, defRadius);
    ball.center = QPoint(width() / 2, height() / 2);
    startTimer(30);
}

void moveDialog::paintEvent(QPaintEvent*){
    QPainter p(this);
    p.setPen (Qt::NoPen);
    p.setBrush(QBrush(QColor(0, 255, 0)));
    p.drawEllipse(ball.center, ball.radius.width(), ball.radius.height());
}

void moveDialog::timerEvent(QTimerEvent*){
    int x = ball.center.x();
    int y = ball.center.y();
    int rx,ry;
    int w = width();
    int h = height();

    //define movement
    x += dx;
    y += dy;

    
    rx = defRadius;
    ry = defRadius;

    //redefine size of the ball
    if (x + defRadius > w){
        rx = w - x;
    }
    else{
        if (x - defRadius < 0){
            rx = x;
        }
    }//XCoord

    if (y + defRadius > h){
        ry = h - y;
    }
    else{
        if (y - defRadius < 0){
            ry = y;
        }
    }//YCoord

    //change direction
    if (ry < defRadius / 2){
        dy = -dy;
    }
    if (rx < defRadius / 2){
        dx = -dx;
    }

    //define new parameters
    ball.center = QPoint(x,y);
    ball.radius = QSize(rx,ry);

    update();
}


