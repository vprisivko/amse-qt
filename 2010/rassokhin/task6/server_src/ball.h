#ifndef BALL_H
#define BALL_H

#include "engineobject.h"

class Ball: public EngineObject {
public:
    Ball(ArcanoidEngine *scene, QGraphicsItem *parent = 0);
    virtual ~Ball(){}

    void advanceItem();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * = 0);

    void resetPosition();
};
#endif // BALL_H
