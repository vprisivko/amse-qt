#include "block.h"

Block::Block(QPointF position, ArcanoidEngine *scene, QGraphicsItem *parent) :
        EngineObject(scene, parent, position) {
    setState(EngineObject::Static);
    resize(QSize(50, 20));
}

void Block::advanceItem() {
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    static QBrush blockBrush(QColor("gray"), Qt::SolidPattern);
    painter->setBrush(blockBrush);
    painter->drawRoundedRect(boundingRect(), 2, 2, Qt::AbsoluteSize);
}
