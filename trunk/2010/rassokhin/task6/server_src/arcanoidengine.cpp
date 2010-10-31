/*
 * Copyright (C) 2007-2008 John-Paul Stanford <jp@stanwood.org.uk>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this program; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include "arcanoidengine.h"

#include "ball.h"
#include "block.h"
#include "board.h"

#include <QtGlobal>

#include <QTimer>

ArcanoidEngine::ArcanoidEngine(const QRectF &sceneRect, QObject *parent) :
    QGraphicsScene(sceneRect, parent)
{
    m_clock = new QTimer(this);
    m_clock->setInterval(250);
    connect(m_clock, SIGNAL(timeout() ), this, SLOT(tick() ));

    m_ball = new Ball(this);
    m_ball->show();
    resetBall();

    m_board = new Board(QPointF(0,0),this);
    m_board->show();

    clear();
}

ArcanoidEngine::~ArcanoidEngine() {
    delete m_ball;
    delete m_board;
    qDeleteAll(m_blocks);
}

void ArcanoidEngine::resetBall() {
    m_ball->setState(EngineObject::Moving);
    m_ball->resetPosition();
}

void ArcanoidEngine::resize(QSize& /*size*/) {
//    unsigned int minTileSizeWidth = size.width() / 30;
//    unsigned int minTileSizeHeight = size.height() / 30;
//
//    m_tileSize = QSize(minTileSizeWidth, minTileSizeHeight);
//
//    foreach(Block *block, m_blocks) {
//        block->resize(m_tileSize);
//    }
//
//    m_ball->resize(m_tileSize);
//    if (m_bomb!=NULL) {
//        m_bomb->resize(m_tileSize);
//    }
//    if (m_board!=NULL) {
//        m_board->resize(m_tileSize);
//    }
//
//    redraw();
//
//    size.setWidth(minTileSizeWidth * 30);
//    size.setHeight(minTileSizeHeight * 30);
}

void ArcanoidEngine::redraw()
{
//    m_ball->resetPixmaps();
//    if (m_bomb != NULL)
//    {
//        m_bomb->resetPixmaps();
//    }
}

void ArcanoidEngine::newLevel(unsigned int level) {
    if (level > 5) {
        level = 5;
    }

    if (level == 1) {
        m_ball->setVelocity( QPointF(15,15) );
    } else if (level % 2 == 0) {
        m_ball->setVelocity( m_ball->velocity()+ QPointF(3,3) );
    }

    m_clock->stop();
    clear();

    m_ball->setState(EngineObject::Moving);

    //Create the bloks
    for (unsigned int i = 0; i < 5; i++)
    {
        unsigned int min = level;
        if (min < 3) {
            min = 3;
        }
        unsigned int max = level + 3;
        if (max < 5) {
            max = 5;
        }
        unsigned int height = (qrand() % (max - min)) + min;

        for(unsigned int j = 0; j< height ;++j) {
            Block *block = new Block(QPointF(i*51, 400 - j*20), this);
            block->show();
        }
    }
}

void ArcanoidEngine::setPaused(bool val)
{
    if (val)
        m_clock->stop();
    else
        m_clock->start();
}

void ArcanoidEngine::tick()
{
    checkCollisions();

    m_ball->advanceItem();
   // m_board->advanceItem();

    // Draw everything
    m_ball->update();
    m_board->update();


    foreach(Block *block, m_blocks)
    {
        block->update();
    }
}

void ArcanoidEngine::checkCollisions()
{
    foreach(Block *block, m_blocks)
    {
//        if (m_ball->boundingRect().intersects(block->boundingRect()) && m_ball->state()
//                == EngineObject::Moving)
//        {
//            // Ball crashed into the building
//            building->destoryTop();
//            m_buildingBlocks--;
//            crashed();
//        }

        if (m_ball->boundingRect().intersects(block->boundingRect())) {
            // Bomb hit a building
            m_blocks.removeOne(block);
            emit onBlockHit();
        }

        if (m_blocks.size()==0) {
            emit levelCleared();
        }
    }
}

void ArcanoidEngine::crashed() {
    m_ball->setState(Ball::Exploded);
}

void ArcanoidEngine::clear() {
    qDeleteAll(m_blocks);
    m_blocks.clear();

    resetBall();
}
