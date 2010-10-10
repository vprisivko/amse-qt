#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <QDialog>
#include <QTimerEvent>
#include <QPainter>

class Dialog: public QDialog{
    Q_OBJECT;

    struct Ball {
        double x;
        double y;
        double vx;
        double vy;
        double width;
        double height;
        int radius;
    };

    Ball myBall;
    int myTimerId;
    QPainter *myPainter;

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
    void timerEvent(QTimerEvent *);
    void paintEvent(QPaintEvent *);
};

#endif // _DIALOG_H_
