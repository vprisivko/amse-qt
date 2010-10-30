#ifndef ROCKET_H
#define ROCKET_H
#include<QString>
#include<QDomDocument>
class Rocket {
public:
    Rocket(int w=100, int h=5, int x=160);
    int widthRock;
    int heightRock;
    int xPosition;
    static QDomElement serialize(Rocket *r,QDomDocument *doc);
};

#endif // ROCKET_H
