#include"Ball.h"

Ball::Ball(){
    restartBall();
}

void Ball::restartBall(){
    xradius = startrad;
    yradius = startrad;
    radius = startrad;
    vx = startvx;
    vy = startvy;
    x = startx;
    y = starty;

}

