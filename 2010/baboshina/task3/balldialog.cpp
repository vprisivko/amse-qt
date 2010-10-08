#include <QRect>
#include <QPoint>
#include <QPainter>

#include "balldialog.h"

ballDialog::ballDialog(QWidget *p):QDialog(p){
    qsrand(time(0));

    b.rx = b.ry = b.r = 15;
    b.x = qrand() % 100 + 15;
    b.y = qrand() % 100 + 15;
    b.dx = qrand() % 10 - 5;
    b.dy = qrand() % 10 - 5;

    timer_id = startTimer(1);
    startTimer(25);
}

void ballDialog::ball::move(int w, int h){
    x += dx;
    y += dy;

    if ((x - r / 2 < 0) || (w - x - r / 2 < 0)) dx *= -1;
    if ((y - r / 2 < 0) || (h - y - r / 2 < 0)) dy *= -1;

    if (x - r < 0) rx = x;
    if (w - x - r < 0) rx = w - x;
    if (y - r < 0) ry = y;
    if (h - y - r < 0) ry = h - y;
}

void ballDialog::paintEvent(QPaintEvent*){
    QPainter p(this);

    p.setBrush(QBrush(Qt::red));
    p.drawEllipse(QPoint(b.x, b.y), b.rx, b.ry);
}

void ballDialog::timerEvent(QTimerEvent* e){
    if (e->timerId() == timer_id) update();
    else b.move(width(), height());
}


