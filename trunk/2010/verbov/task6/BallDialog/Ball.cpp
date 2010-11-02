#include <QTime>
#include "Ball.h"

Ball::Ball(int rx, int ry, int dx, int dy, int tableWidth) {
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    myXCoord = qrand() % tableWidth;
    myYCoord = qrand() % tableWidth;
    myXRadius = myInitialXRadius = rx;
    myYRadius = myInitialYRadius = ry;
    myDx = dx;
    myDy = dy;
}

int Ball::getX() const {
    return myXCoord;
}

int Ball::getY() const {
    return myYCoord;
}

int Ball::getXRadius() const {
    return myXRadius;
}

int Ball::getYRadius() const {
    return myYRadius;
}

void Ball::setDirection(int dx, int dy) {
    myDx = dx;
    myDy = dy;
}

void Ball::setRadius(int rx, int ry) {
    myXRadius = rx;
    myYRadius = ry;
}

bool Ball::move(int width, int height, const Racket &racket) {
    myXCoord += myDx;
    myYCoord += myDy;
    if (myXCoord - myXRadius < 0 || myXCoord + myXRadius > width) {
            myDx = -myDx;
            myXRadius /= 2;
    } else if (myYCoord - myYRadius < 0 || (myYCoord + myYRadius > height - racket.getHeight() &&
                                            myXCoord > racket.getX() && myXCoord < racket.getX() + racket.getWidth())) {
            myDy = -myDy;
            myYRadius /= 2;
    } else if (myYCoord - myYRadius > height) {
        return false;
    } else {
            if (myXRadius < myInitialXRadius) {
                    myXRadius++;
            } else if (myYRadius < myInitialYRadius) {
                    myYRadius++;
            }
    }
    return true;
}

void Ball::recalculatePosition(int width, int height) {
    if (myXCoord < myXRadius) {
            myXCoord = myXRadius;
    }
    if (myYCoord < myYRadius) {
            myYCoord = myYRadius;
    }
    if (myXCoord > width - myXRadius) {
            myXCoord = width - myXRadius;
    }
    if (myYCoord > height - myYRadius) {
            myYCoord = height - myYRadius;
    }
}

QDomElement Ball::createBallElement(QDomDocument &document, const QString &name, const QString &type, int value) {
    QDomElement element = document.createElement(name);
    element.setAttribute("type", type);
    element.appendChild(document.createTextNode(QString::number(value)));
    return element;
}

void Ball::reset(int tableWidth) {
    myXRadius = myInitialXRadius;
    myYRadius = myInitialYRadius;
    myXCoord = qrand()%(tableWidth + 1);
    myYCoord = qrand()%(tableWidth + 1);
}

QDomDocument Ball::serialize() {
    QDomDocument resultDocument;

    QDomElement ballElement = resultDocument.createElement("ball");
    resultDocument.appendChild(ballElement);

    ballElement.appendChild(createBallElement(resultDocument, "coordinate", "x", myXCoord));
    ballElement.appendChild(createBallElement(resultDocument, "coordinate", "y", myYCoord));
    ballElement.appendChild(createBallElement(resultDocument, "radius", "x", myXRadius));
    ballElement.appendChild(createBallElement(resultDocument, "radius", "y", myYRadius));
    ballElement.appendChild(createBallElement(resultDocument, "delta", "x", myDx));
    ballElement.appendChild(createBallElement(resultDocument, "delta", "y", myDy));

    return resultDocument;
}
