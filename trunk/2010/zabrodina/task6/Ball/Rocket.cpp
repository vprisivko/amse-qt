#include"Rocket.h"

Rocket::Rocket(int w, int h, int x){
    widthRock = w;
    heightRock = h;
    xPosition = x;
}
QDomElement Rocket::serialize(Rocket *r, QDomDocument *doc){
    QDomElement rocket = doc->createElement("Rocket");
     doc->appendChild(rocket);
     QDomElement pos = doc->createElement("position");
     pos.setAttribute("xPositon",r->xPosition);
     rocket.appendChild(pos);
     QDomElement width = doc->createElement("width");
     width.setAttribute("widthRock",r->widthRock);
     rocket.appendChild(width);
     QDomElement height = doc->createElement("height");
     height.setAttribute("heightRock",r->heightRock);
     rocket.appendChild(height);
    return rocket;

}
