#ifndef BALL_H
#define BALL_H

#include <QDomDocument>
#include <QDomElement>
#include "Racket.h"

class Ball
{

public:
    Ball(int rx, int ry, int dx, int dy, int tableWidth);

    void setDirection(int dx, int dy);
    void setRadius(int rx, int ry);
    void reset(int tableWidth);

    bool move(int width, int height, const Racket &racket);
    void recalculatePosition(int width, int height);

    int getX() const;
    int getY() const;
    int getXRadius() const;
    int getYRadius() const;

    QDomDocument serialize();

private:
    int myXCoord, myYCoord, myXRadius, myYRadius, myDx, myDy;
    int myInitialXRadius, myInitialYRadius;

private:
    QDomElement createBallElement(QDomDocument &document, const QString &name, const QString &type, int value);

};

#endif // BALL_H
