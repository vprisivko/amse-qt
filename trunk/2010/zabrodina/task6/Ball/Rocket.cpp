#include"Rocket.h"

Rocket::Rocket(int w, int h, int x){
    widthRock = w;
    heightRock = h;
    xPosition = x;
}
QDomElement Rocket::serialize(Rocket *r, QDomDocument *doc){
    QDomElement rocket = doc->createElement("Rocket");
    rocket.setAttribute("xPositon",r->xPosition);
    rocket.setAttribute("widthRock",r->widthRock);
     doc->appendChild(rocket);
    return rocket;

}
