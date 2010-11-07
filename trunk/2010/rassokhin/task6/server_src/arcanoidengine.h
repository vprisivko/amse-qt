#ifndef ARCANOIDENGINE_H
#define ARCANOIDENGINE_H

#include <QGraphicsScene>
#include <QList>
#include <QTimer>
#include "ball.h"
#include "block.h"
#include "board.h"

class ArcanoidEngine : public QGraphicsScene {
Q_OBJECT;

public:
    /** The different states that the game can be in */
    enum State {
        BeforeFirstGame,
        Running,
        BetweenLevels,
        Paused,
        GameOver
    };

    ArcanoidEngine(const QRectF & sceneRect, QObject * parent = 0);

    ~ArcanoidEngine();
    void resize( QSize& size );

    /**
     * This is called to pause the game.
     * \param val True if pased, otherwise false
     */
    void setPaused(bool val);

    /**
     * Used to move ball to the start position
     */
    void resetBall();

    void newLevel(unsigned int level = 1);
    void nextLevel() {
        newLevel(m_level);
    }


    /**
     * Used to return the game sate
     * \return The game state
     */
    ArcanoidEngine::State state() const;

signals:
    void onBallCrash();
    void onBlockHit();

    /**
     * This is emitted when the level has been cleared of all blocks
     */
    void onLevelClear();

    /**
     * This is emitted when the lives change
     * \param lives The new lives
     */
    void livesChanged( unsigned int lives );

    /**
     * This is emitted when the game state changes
     * \param state The new game state
     */
    void stateChanged( ArcanoidEngine::State state );



public slots:
    void moveBoardLeft();
    void moveBoardRight();

    /**
     * Used to end the game
     */
    void closeGame();

    /**
     * Used to start a new game
     */
    void newGame();

private slots:

    /** This is called once a second to update and draw all the game objects */
    void tick();
    /**
     * This is called when a bomb hits a building
     */
    void onBlockHitted();

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

    /**
     * This is used to remove all the current game objects, usually called before
     * stating a new level
     */
    void clear();

    /**
     * This is used to check for any collisions of the blocks or ball
     */
    void checkCollisions();

    void setState(State state) {
        m_state = state;
        emit stateChanged(m_state);
    }

    QTimer *m_clock;

    Board *m_board;
    Ball *m_ball;
    QList<Block *> m_blocks;

    State m_state;
    unsigned int m_level;
    unsigned int m_lives;

};

#endif // ARCANOIDENGINE_H
