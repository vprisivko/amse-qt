#ifndef RACKET_H
#define RACKET_H

#include <QDomDocument>
#include <QDomElement>

class Racket
{

public:
    Racket(int width, int height, int initialX = 0);
    int getX() const;
    int getWidth() const;
    int getHeight() const;
    void move(int dx);
    void recalculatePosition(int width);

    QDomDocument serialize();

private:
    int myX;
    const int myWidth, myHeight;

private:
    QDomElement createRacketElement(QDomDocument &document, const QString &name, int value);

};

#endif // RACKET_H
