#include"State.h"
State::State(){
    defLives = 3;
    livesleft = defLives;
    b = new Ball();
    r = new Rocket();
}
QDomElement State::serialize(State *st, QDomDocument *doc){
    QDomElement stateEl = doc->createElement("State");
    stateEl.setAttribute("livesleft",st->livesleft);
    stateEl.setAttribute("width",st->widthDialog);
    stateEl.appendChild( Rocket::serialize(st->r,doc));
    doc->appendChild(stateEl);
    return stateEl;
}
