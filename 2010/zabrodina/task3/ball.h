#ifndef BALL_H
#define BALL_H
#include<QPushButton>
#include<QDialog>
#include<QPainter>
#include<QPaintEvent>
#include<QTimerEvent>
#include<QTimer>
class BallDialog: public QDialog {
 Q_OBJECT;
public:
    int xradius, yradius, radius;
    int x, y;
    int vx, vy;
    QPainter *p;
    QTimer *bTimer;
    int compressionx, compressiony; //change circle to ellipse //
    BallDialog( int rad = 10, int _vx = 1, int _vy = 2 );
    void paintEvent( QPaintEvent * );
    void press( int axes );
public slots:
    void timeEvent();
};

#endif // BALL_H
