#ifndef ENGINEOBJECT_H
#define ENGINEOBJECT_H

#include <QString>
#include <QPainter>
#include <QPointF>
#include <QGraphicsItem>

class ArcanoidEngine;

class EngineObject: public QGraphicsItem {
public:
    enum State {
        Moving, Static
    };

    EngineObject(ArcanoidEngine *scene, QGraphicsItem *parent = 0,
                 QPointF position = QPointF(0, 0),
                 QPointF velocity = QPointF(0, 0));
    virtual ~EngineObject() {}

    QPointF velocity() const;
    QPointF position() const;
    QRectF boundingRect() const;
    EngineObject::State state() const;

    void update();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * = 0);

    void resize(const QSize& size);

    void setVelocity(QPointF velocity);
    void setPosition(QPointF pos);
    void setState(EngineObject::State state);

protected:
    QPointF m_pos; //position
    QRectF m_nextBoundingRect; //next position and size
    QPointF m_velocity;
    QSizeF m_size;

protected:
    ArcanoidEngine *m_scene;

    State m_state;
    QSize m_lastSize;
};

#endif
