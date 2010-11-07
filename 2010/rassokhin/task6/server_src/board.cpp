#include "board.h"

Board::Board(QPointF position, ArcanoidEngine *scene, QGraphicsItem *parent)
        : EngineObject(scene, parent, position) {
    setState(EngineObject::Static);
    resize(QSize(100, 10));
}

void Board::advanceItem() {
}

void Board::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    static QBrush boardBrush(QColor("green"), Qt::SolidPattern);
    painter->setBrush(boardBrush);
    painter->drawRoundedRect(boundingRect(), 2, 2, Qt::AbsoluteSize);
}
