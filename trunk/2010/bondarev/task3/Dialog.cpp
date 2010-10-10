#include "Dialog.h"

Dialog::Dialog(QWidget *parent):
        QDialog(parent) {
    startTimer(10);

    qsrand(time(0));

    myBall.radius = 30;
    myBall.x = qrand() % this->width() / 2 + myBall.radius;
    myBall.y = qrand() % this->height() / 2 + myBall.radius;
    myBall.vx = qrand() % 1 + 3;
    myBall.vy = qrand() % 1 + 3;
    myBall.width = myBall.radius;
    myBall.height = myBall.radius;

    myPainter = new QPainter();
}

void Dialog::timerEvent(QTimerEvent *) {
    myBall.x += myBall.vx;
    myBall.y += myBall.vy;

    if (myBall.x < myBall.radius) {
        myBall.width = myBall.x * 2;
    } else if (myBall.x > width() - myBall.radius) {
        myBall.width = (width() - myBall.x) * 2;
    }
    if (myBall.width < myBall.radius) {
        myBall.vx = -myBall.vx;
    }

    if (myBall.y < myBall.radius) {
        myBall.height = myBall.y * 2;
    } else if (myBall.y > height() - myBall.radius) {
        myBall.height = (height() - myBall.y) * 2;
    }
    if (myBall.height < myBall.radius) {
        myBall.vy = -myBall.vy;
    }

    update();
}

void Dialog::paintEvent(QPaintEvent *) {
    QRadialGradient gradient(myBall.x + myBall.width / 6, myBall.y - myBall.height / 6, myBall.radius);
    gradient.setColorAt(1, QColor::fromRgbF(0, 0, 1, 1));
    gradient.setColorAt(0, QColor::fromRgbF(1, 1, 1, 1));

    myPainter->begin(this);
    myPainter->setBrush(gradient);
    myPainter->setPen(Qt::NoPen);
    myPainter->drawEllipse(myBall.x - myBall.width / 2, myBall.y - myBall.height / 2, myBall.width, myBall.height);
    myPainter->end();
}

Dialog::~Dialog() {
    delete myPainter;
}
