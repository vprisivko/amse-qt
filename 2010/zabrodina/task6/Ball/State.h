#ifndef STATE_H
#define STATE_H
#include"Ball.h"
#include"Rocket.h"
class State {
public:
    int defLives;
    int livesleft;
    Ball *b;
    Rocket *r;
    static const int widthDialog = 600;
    State();
    static QDomElement serialize(State *st,QDomDocument *doc);

};

#endif // STATE_H
