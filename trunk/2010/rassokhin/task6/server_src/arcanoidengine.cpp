#include "arcanoidengine.h"

#include "ball.h"
#include "block.h"
#include "board.h"

#include <QtGlobal>
#include <QTimer>
#include <qmath.h>

ArcanoidEngine::ArcanoidEngine(const QRectF &sceneRect, QObject *parent) :
        QGraphicsScene(sceneRect, parent), m_state(BeforeFirstGame) {
    m_clock = new QTimer(this);
    connect(m_clock, SIGNAL(timeout()), SLOT(tick()));

    m_ball = new Ball(this);
    m_ball->show();
    resetBall();

    m_board = new Board(sceneRect.topLeft()+QPointF(0,30), this);
    m_board->show();

    clear();

    connect(this, SIGNAL(onBlockHit()), SLOT(onBlockHitted()));
    connect(this, SIGNAL(onBallCrash()), SLOT(onBallCrashed()));
    connect(this, SIGNAL(onLevelClear()), SLOT(onLevelCleared()));
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

unsigned int max(unsigned int a, unsigned int b) {
    return (a > b)? a : b;
}
unsigned int min(unsigned int a, unsigned int b) {
    return (a < b)? a : b;
}


void ArcanoidEngine::newLevel(unsigned int level) {
    m_clock->stop();
    clear();

    level = max(level, 5);
    level = min(level, 1);

    QPointF v = m_ball->velocity();
    v.setX(abs(v.x()));
    v.setY(abs(v.y()));
    if (level == 1) {
        v = QPointF(5, 5);
    }
    else if (level % 2 == 0) {
        m_ball->setVelocity(v + QPointF(1, 1) );
    }
    m_ball->setVelocity(v);
    m_ball->resetPosition();

    //Create the blocks
    QRectF scSize = sceneRect();
    for (unsigned int i = 0; i < floor(scSize.width()/50); i++) {
        unsigned int minH = max(level, 1);
        unsigned int maxH = min(level + 3, 5);
        unsigned int height = (qrand() % (maxH - minH)) + minH;
        for(unsigned int j = 0; j < height; ++j) {
            QPointF pos(scSize.left()+ (i * 50), scSize.bottom() - ((j+1) * 20));
            Block *block = new Block(pos, this);
            m_blocks.append(block);
            block->show();
        }
    }

    setState(Running);
    m_clock->start(50);

    emit livesChanged(m_lives);
}

void ArcanoidEngine::setPaused(bool paused) {
    if (m_state == Paused && paused == false) {
        m_clock->start(50);
        setState(Running);
    }
    else if (m_state == Running && paused == true) {
        m_clock->stop();
        setState(Paused);
    }
}

void ArcanoidEngine::tick() {
    checkCollisions();
    m_ball->advanceItem();
    // update everything
    update();
}

void ArcanoidEngine::checkCollisions() {
    QRectF ballRect = m_ball->boundingRect();
    foreach(Block *block, m_blocks) {
        if (!ballRect.intersect(block->boundingRect()).isEmpty()) {
            removeItem(block);
            m_blocks.removeOne(block);
            QPointF vel = m_ball->velocity();
            vel.setY(-vel.y());
            m_ball->setVelocity(vel);
            emit onBlockHit();
        }
    }
    if (m_blocks.size() == 0) {
        emit onLevelClear();
        return;
    }
    if (ballRect.top() <= sceneRect().top()+10) {
        emit onBallCrash();
        return;
        // ball fails
    }
    if (ballRect.intersects(m_board->boundingRect())) {
        // отражение
        QPointF vel = m_ball->velocity();
        vel.setY(-vel.y());
        m_ball->setVelocity(vel);
        ////TODO: нормальное отражение по x
    }
}

void ArcanoidEngine::clear() {
    qDeleteAll(m_blocks);
    m_blocks.clear();

    resetBall();
}

void ArcanoidEngine::moveBoardLeft() {
    QPointF pos = m_board->position();
    qreal x = pos.x();
    x -= 40.0f;
    if (x < sceneRect().left())
        x = sceneRect().left();
    pos.setX(x);
    m_board->setPosition(pos);
}

void ArcanoidEngine::moveBoardRight() {
    QPointF pos = m_board->position();
    qreal x = pos.x();
    x += 40.0f;
    if (x > sceneRect().right()-m_board->boundingRect().width())
        x = sceneRect().right()-m_board->boundingRect().width();
    pos.setX(x);
    m_board->setPosition(pos);
}

void ArcanoidEngine::onBlockHitted() {
//    unsigned int bonus = SCORE_INCREMENT * m_level;
//    m_score += bonus;emit
//    scoreChanged(m_score);
//    m_scoreLeftBeforeNewLife -= bonus;
//    if (m_scoreLeftBeforeNewLife <= 0)
//    {
//        m_scoreLeftBeforeNewLife = NEW_LIVE_AT_SCORE;
//        m_lives++;
//        emit livesChanged(m_lives);
//    }
}

ArcanoidEngine::State ArcanoidEngine::state() const {
    return m_state;
}

void ArcanoidEngine::onBallCrashed() {
    m_lives--;
    emit livesChanged(m_lives);
    if (m_lives <= 0) {
        setState(GameOver);
        m_clock->stop();
    }
    else {
        setPaused(true);
        QPointF v = m_ball->velocity();
        v.setX(abs(v.x()));
        v.setY(abs(v.y()));
        m_ball->setVelocity(v);
        resetBall();
    }
}

void ArcanoidEngine::onLevelCleared() {
    if (m_state == Running) {
        m_clock->stop();
        m_level++;
        setState(BetweenLevels);
    }
}

void ArcanoidEngine::newGame() {
    m_clock->stop();

    m_level = 1;
    m_lives = 3;

    emit livesChanged(m_lives);

    newLevel();
}

void ArcanoidEngine::closeGame() {
    if (m_state != BeforeFirstGame && m_state != GameOver) {
        m_clock->stop();
        setState(GameOver);
    }
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

