/* kdegames.bomber.board.h
 * Copyright (C) 2007-2008 John-Paul Stanford <jp@stanwood.org.uk>
 * Copyright 2010 Rassokhin Vladislav <vladrassokhin@gmail.com>
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

#ifndef ARCANOIDENGINE_H
#define ARCANOIDENGINE_H

#include <QGraphicsScene>
#include <QList>
#include <QTimer>
#include <QTimer>
#include "ball.h"
#include "block.h"
#include "board.h"

class ArcanoidEngine : public QGraphicsScene {
Q_OBJECT;

public:

    /**
     * The constructor used to create the board.
//     * \param renderer The Render used to renderer game objects
//     * \param canvas The object were the games objects are drawn onto
     * \param parent The widget which the board is inserted into
     */
    explicit ArcanoidEngine(const QRectF & sceneRect, QObject * parent = 0);

    ~ArcanoidEngine();
    /**
     * This is called when the game board is resized
     * \param size The new tile size used on the game board
     */
    void resize( QSize& size );

    /**
     * This will redraw the game board
     */
    void redraw();

    /**
     * This is called to pause the game.
     * \param val True if pased, otherwise false
     */
    void setPaused( bool val);

    /**
     * Used to move ball to the start position
     */
    void resetBall();
    void newLevel(unsigned int level = 1);

    signals:
    /**
     * This is emitted when a plane crashes into a building
     */
    void onBallCrash();

    /**
     * This signal is emitted when a bomb hits a building and before it's exploding
     * animation starts
     */
    void onBlockHit();

    /**
     * This is emitted when the level has been cleared of all buildings
     */
    void levelCleared();


private slots:
    /** This is called once a second to update and draw all the game objects */
    void tick();

private:

    /**
     * This is used to remove all the current game objects, usually called before
     * stating a new level
     */
    void clear();

    /**
     * This is used to check for any collisions of the blocks or ball
     */
    void checkCollisions();

    /**
     * This is called when a ball crashes...
     */
    void crashed();

//    KGameRenderer *m_renderer;
    QSize m_tileSize;

    QTimer *m_clock;

    Board *m_board;
    /** This points to the ball object used in the level */
    Ball *m_ball;

    /** This contains all the blocks in the current level */
    QList<Block *> m_blocks;
};

#endif // ARCANOIDENGINE_H
