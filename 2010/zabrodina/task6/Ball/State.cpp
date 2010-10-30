#include"State.h"
State::State(){
    defLives = 3;
    livesleft = defLives;
    b = new Ball();
    r = new Rocket();
}
QDomElement State::serialize(State *st, QDomDocument *doc){
    QDomElement stateEl = doc->createElement("State");
     doc->appendChild(stateEl);
     QDomElement livLeft = doc->createElement("Lives");
     livLeft.setAttribute("livesleft",st->livesleft);
     stateEl.appendChild(livLeft);
     QDomElement w = doc->createElement("widthDialog");
     w.setAttribute("widthDialog",st->widthDialog);
     stateEl.appendChild(w);
     QDomElement rocket = st->r->serialize(st->r,doc);
     stateEl.appendChild(rocket);
    return stateEl;
}
