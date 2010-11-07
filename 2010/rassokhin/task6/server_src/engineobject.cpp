#include <QtGlobal>

#include "engineobject.h"
#include "arcanoidengine.h"

EngineObject::EngineObject(ArcanoidEngine *scene, QGraphicsItem *parent,
                           QPointF position, QPointF velocity)
        : QGraphicsItem(parent, scene), m_scene(scene) {
    m_pos = position;
    m_velocity = velocity;
    m_size = QSizeF(32, 64);
    m_state = Static;
    m_nextBoundingRect.setSize(m_size);
}

void EngineObject::setPosition(QPointF pos) {
    m_pos = pos;
    m_nextBoundingRect.moveTo(m_pos);
}

void EngineObject::update() {
}

void EngineObject::resize(const QSize& tileSize) {
    m_size = tileSize;
//    m_lastSize = tileSize;
//    if (m_state == Moving) {
//        setRenderSize(QSize(
//            m_relativeWidth * tileSize.width(),
//            m_relativeHeight * tileSize.height()
//        ));
//    }
//    else {
//        setRenderSize(QSize(
//            EXPLOSION_RELATIVE_SIZE_W * tileSize.width(),
//            EXPLOSION_RELATIVE_SIZE_H * tileSize.height()
//        ));
//    }
    //moveTo(m_scene->mapPosition(QPointF(m_xPos, m_yP+os)));
}

void EngineObject::setVelocity(QPointF velocity) {
    m_velocity = velocity;
}

void EngineObject::setState(EngineObject::State state) {
    m_state = state;
}
void EngineObject::paint(QPainter *painter,
            const QStyleOptionGraphicsItem *,
            QWidget *) {
painter->drawRect(boundingRect());
}

QPointF EngineObject::position() const {
    return m_pos;
}

EngineObject::State EngineObject::state() const {
    return m_state;
}

QPointF EngineObject::velocity() const {
    return m_velocity;
}

QRectF EngineObject::boundingRect() const {
    return QRectF(m_pos, m_size);
}
