#include <QDebug>
#include <QPainter>
#include "Widget.h"


Widget::Widget(QWidget* p): QDialog(p) {
    setMinimumSize( 400, 300 );
    qsrand(time(0));

    b.r = 15;
    b.x = qrand() % 200 + 20;
    b.y = qrand() % 200 + 20;

    b.dx = qrand() % 100;
    b.dy = qrand() % 100;

    b.rx = b.ry = 0;

    timer_id = startTimer(35);
    startTimer(1);
}

void Widget::timerEvent(QTimerEvent* e){
    if (e->timerId() == timer_id ){
        update();
    } else {
        moveElipse();
    }
}


void Widget::paintEvent(QPaintEvent* e){
    QRect r = e->rect();
    QPainter p(this);
    p.setBrush(Qt::gray);
    p.drawRect(r);
    b.rx = b.ry = b.r;
    
    if (b.x < b.r) {
        b.rx = b.x;
    }
    if (r.width() - b.x < b.r) {
        b.rx = (r.width() - b.x);
    }
    if (b.y < b.r) {
        b.ry = b.y;
    }
    if (r.height() - b.y < b.r) {
        b.ry = (r.height() - b.y);
    }
    p.setBrush(Qt::red);
    p.drawEllipse(b.x - b.rx, b.y - b.ry, b.rx * 2, b.ry * 2);

}


void Widget::moveElipse(){
   // qDebug() << b.rx << " dx- "<< b.ry << " dy- "<< b.r << " r- ";
    if (b.x < b.r / 2) {
        b.dx = -b.dx;
    }
    if (b.y < b.r / 2) {
        b.dy = -b.dy;
    }

    if (rect().width() - b.x < b.r / 2) {
        b.dx = -qAbs(b.dx);
    }
    if (rect().height() - b.y < b.r / 2) {
        b.dy = -qAbs(b.dy);
    }

    b.x += b.dx/500;
    b.y += b.dy/500;
}

