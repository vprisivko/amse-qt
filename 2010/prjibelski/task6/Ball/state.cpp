#include <iostream>
#include <ctime>
#include <cstdlib>

#include "state.h"

// ========= class Ball =========
Ball::Ball() {
    restart();
}

void Ball::restart() {
    x = stx;
    y = sty;
    ax = stax;
    ay = stay;
    vx = (rand() % 20) / 4.0;
    vy = stvy;
    compDirectionX = 0;
    compDirectionY = 0;
    radius = stR;
    rx = radius;
    ry = radius;
}

// ========= end class Ball =========


// ========= class Plate =========
Plate::Plate() {
    restart();
}

void Plate::restart() {
    x = stx;
    height = sth;
    width = stw;
}

QDomElement Plate::serialize( Plate * object , QDomDocument * doc ) {
    QDomElement plEl = doc->createElement("plate");
    plEl.setAttribute("x",object->x);
    plEl.setAttribute("width", object->width );
    return plEl;
}

// ========= end class Plate =========

// ========= class State =========
State::State( int ww, Plate * pl )
{
    srand( time(0) );

    windowWidth = ww;
    if ( pl == 0 ) {
        plate = new Plate();
    } else {
        plate = pl;
    }
    ball = new Ball();
    newGame();
}

State::~State() {
    delete plate;
    delete ball;
}

void State::restart() {
    fail = false;
    plate->restart();
    ball->restart();
}

void State::newGame() {
    restart();
    livesLeft = startLives;
}

QDomElement State::serialize( State * object, QDomDocument * doc ) {
    QDomElement stEl = doc->createElement("state");
    stEl.setAttribute("lives",object->livesLeft);
    stEl.setAttribute("window_width", object->windowWidth );
    stEl.appendChild( Plate::serialize(object->plate, doc) );
    return stEl;
}

// ========= end class State =========
