#include "Racket.h"

Racket::Racket(int width, int height, int initialX) : myWidth(width), myHeight(height) {
    myX = initialX;
}

int Racket::getX() const {
    return myX;
}

int Racket::getWidth() const {
    return myWidth;
}

int Racket::getHeight() const {
    return myHeight;
}

void Racket::move(int dx) {
    myX += dx;
}

void Racket::recalculatePosition(int width) {
    if (myX < 0) {
        myX = 0;
    }
    if (myX + myWidth > width) {
        myX = width - myWidth;
    }
}

QDomElement Racket::createRacketElement(QDomDocument &document, const QString &name, int value) {
    QDomElement element = document.createElement(name);
    element.setAttribute("value", value);
    return element;
}

QDomDocument Racket::serialize() {
    QDomDocument resultDocument;
    resultDocument.appendChild(resultDocument.createElement("racket"));
    resultDocument.appendChild(createRacketElement(resultDocument, "x", myX));
    resultDocument.appendChild(createRacketElement(resultDocument, "width", myWidth));
    resultDocument.appendChild(createRacketElement(resultDocument, "height", myHeight));
    return resultDocument;
}
