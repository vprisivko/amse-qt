#include "ball.h"

#include "arcanoidengine.h"
#include "engineobject.h"

Ball::Ball(ArcanoidEngine *scene, QGraphicsItem *parent)
        :EngineObject(scene, parent) {
    resetPosition();
    setState(EngineObject::Moving);
    resize(QSize(20, 20));
}

void Ball::resetPosition() {
    m_pos = m_scene->sceneRect().topLeft() + QPointF(50,50);
}

void Ball::advanceItem() {
    QRectF borders;
    borders = m_scene->sceneRect();

    m_pos += velocity();

    if (m_pos.x() < borders.x()) {
        m_pos.setX( borders.x());
        m_velocity.setX(-m_velocity.x());
    }
    if (m_pos.x() >  borders.width()) {
        m_pos.setX( borders.width());
        m_velocity.setX(-m_velocity.x());
    }
    if (m_pos.y() <  borders.y()) {
        m_pos.setY( borders.y());
        m_velocity.setY(-m_velocity.y());
    }
    if (m_pos.y() >  borders.height()) {
        m_pos.setY( borders.height());
        m_velocity.setY(-m_velocity.y());
    }
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    static QBrush ballBrush(QColor("red"), Qt::SolidPattern);
    painter->setBrush(ballBrush);
    painter->drawEllipse(boundingRect());
}
