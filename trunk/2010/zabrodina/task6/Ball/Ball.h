#ifndef BALL_H
#define BALL_H
#include<QString>
class Ball {
public:
        int xradius, yradius, radius;
        int x, y;
        static const int startx = 20;
        static const int starty = 20;
        int vx, vy;
        static const int startvx = 1;
        static const int startvy = 2;
        static const int startrad = 20;
        Ball();
        void restartBall();

};

#endif // BALL_H
