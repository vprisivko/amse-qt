#ifndef BALLWIDGET_H
#define BALLWIDGET_H
#include <QWidget>

class BallWidget : public QWidget {
    Q_OBJECT;

private:
    int BallRadius;
    double mySpeed;
    double myAngle;
    double myCurrentX,myCurrentY;
    double myDX,myDY;

public:
    BallWidget(int BallRadius = 20, QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
};

#endif // BALLWIDGET_H
