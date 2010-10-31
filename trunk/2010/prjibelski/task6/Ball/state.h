#ifndef STATE_H
#define STATE_H

#include <QString>
#include <QDomDocument>
#include <iostream>

//Class plate
class Plate {
public:
    Plate();
    void restart();

    static QDomElement serialize( Plate * object, QDomDocument * doc );

    int x;
    int height;
    int width;

    int getDx() {
        return dx;
    }

private:
    static const int stx = 50;
    static const int sth = 7;
    static const int stw = 140;
    static const int dx = 20;
};


class Ball {
public:
    Ball();
    void restart();

    double radius;
    int compDirectionX;
    int compDirectionY;
    double x, y;
    double vx, vy;
    double ax, ay;
    double rx, ry;

private:
    static const double stR = 20.0;
    static const double stx = 20;
    static const double sty = 20;
    static const double stvx = 0.6;
    static const double stvy = 1.0;
    static const double stax = 0.013;
    static const double stay = 0.2;
};

class State
{
public:
    State( int ww, Plate * pl = 0 );
    ~State();

    static QDomElement serialize( State * object, QDomDocument * doc );

    int livesLeft;
    int windowWidth;
    bool fail;

    void newGame();
    void restart();

    Plate * plate;
    Ball * ball;

    static const int startLives = 3;
};


#endif // STATE_H
