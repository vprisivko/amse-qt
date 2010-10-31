/* kdegames.bomber.bomberwidget.h
 * Copyright (C) 2007-2008 John-Paul Stanford <jp@stanwood.org.uk>
 * Copyright 2010 Stefan Majewsky <majewsky@gmx.net>
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

#ifndef ARCANOIDVIEWWIDGET_H
#define ARCANOIDVIEWWIDGET_H

#include "arcanoidengine.h"
#include <QGraphicsView>
#include <QTimer>

class ArcanoidViewWidget : public QGraphicsView {
    Q_OBJECT;
public:
    /** The different states that the game can be in */
    enum State
    {   BeforeFirstGame, Running, BetweenLevels, Paused, Suspended, GameOver};

    explicit ArcanoidViewWidget (ArcanoidEngine * engine, QWidget *parent = 0 );
    ~ArcanoidViewWidget();

    /**
     * Used to return the game sate
     * \return The game state
     */
    ArcanoidViewWidget::State state() const;
public slots:
    /**
     * Used to end the game
     */
    void closeGame();

    /**
     * Used to start a new game
     */
    void newGame();

    /**
     * Used to pause the game
     * \param paused True to pause the game, False to resume the game
     */
    void setPaused( bool paused );

    /**
     * Used to toggle the suspended game state. If val is true and the state is currently running,
     * them set the sate to suspended. If value is false and the state is suspended, set the sate to running.
     * \param value True to set state to suspended, False to set state to running.
     */
    void setSuspended( bool value);

    signals:
    /**
     * This is emitted when the game is over
     */
    void gameOver();

    /**
     * This is emitted when the lives change
     * \param lives The new lives
     */
    void livesChanged( unsigned int lives );

    /**
     * This is emitted when the game state changes
     * \param state The new game state
     */
    void stateChanged( ArcanoidViewWidget::State state );

private slots:
    void tick();

    /**
     * This is called when a bomb hits a building
     */
    void onBlockHit();

    /**
     * This slot is called when a level has been cleared to change the state and get
     * ready for the next level.
     */
    void onLevelCleared();

    /**
     * This slot is called when the ball drops under window
     */
    void onBallCrashed();

private:
    virtual void resizeEvent( QResizeEvent *event );
    void redraw();

    void newLevel();

    void closeLevel();

    State m_state;
    unsigned int m_level;
    unsigned int m_lives;

    ArcanoidEngine * m_engine;

    QTimer *m_clock;
};

#endif // ARCANOIDVIEWWIDGET_H
