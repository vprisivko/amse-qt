#ifndef BOARD_H
#define BOARD_H

#include "engineobject.h"

class Board : public EngineObject {
public:
    Board(QPointF position, ArcanoidEngine *scene, QGraphicsItem *parent = 0);
    virtual ~Board(){}

    void advanceItem();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * = 0);
};

#endif // BOARD_H
