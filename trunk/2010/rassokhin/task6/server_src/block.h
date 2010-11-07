#ifndef BLOCK_H
#define BLOCK_H

#include "engineobject.h"

class Block : public EngineObject {
public:
    Block(QPointF position, ArcanoidEngine *scene, QGraphicsItem *parent = 0);
    virtual ~Block(){}

    void advanceItem();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * = 0);
};

#endif
