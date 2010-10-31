/*
 * Copyright (C) 2007-2008 John-Paul Stanford <jp@stanwood.org.uk>
 * Copyright 2010 Stefan Majewsky <majewsky@gmx.net>
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
#include "arcanoidviewwidget.h"
#include <QPalette>
#include <QTimer>
#include <QSize>
#include <QResizeEvent>

static const unsigned int GAME_TIME_DELAY = 100;
static const unsigned int TICKS_PER_SECOND = 1000 / GAME_TIME_DELAY;

ArcanoidViewWidget::ArcanoidViewWidget(ArcanoidEngine *engine, QWidget *parent) :
        QGraphicsView(engine,parent),
    m_state(BeforeFirstGame), m_level(0),m_lives(2),m_engine(engine)
{
    connect(m_engine, SIGNAL(onBallCrash()), this, SLOT(onBallCrashed()));
    connect(m_engine, SIGNAL(onBlockHit()), this, SLOT(onBlockHit()));
    connect(m_engine, SIGNAL(levelCleared()), this, SLOT(onLevelCleared()));

    m_clock = new QTimer(this);
    m_clock->setInterval(GAME_TIME_DELAY);

    connect(m_clock, SIGNAL(timeout() ), this, SLOT(tick() ));
}

ArcanoidViewWidget::~ArcanoidViewWidget() {}



void ArcanoidViewWidget::closeGame() {
    if (m_state != BeforeFirstGame && m_state != GameOver) {
        closeLevel();

        m_state = GameOver;
        emit stateChanged(m_state);
        emit gameOver();

        redraw();
    }
}

void ArcanoidViewWidget::newGame() {
    closeGame();

    m_level = 1;
    m_lives = 3;

    emit livesChanged(m_lives);

    newLevel();
}

void ArcanoidViewWidget::setPaused(bool val)
{
    if (m_state == Paused && val == false)
    {
        m_clock->start();
        m_engine->setPaused(false);
        m_state = Running;
        emit stateChanged(m_state);
    }
    else if (m_state == Running && val == true)
    {
        m_clock->stop();
        m_engine->setPaused(true);
        m_state = Paused;
        emit stateChanged(m_state);
    }

    redraw();
}

void ArcanoidViewWidget::setSuspended(bool val)
{
    if (m_state == Suspended && val == false)
    {
        m_clock->start();
        m_engine->setPaused(false);
        m_state = Running;
        emit stateChanged(m_state);
    }
    if (m_state == Running && val == true)
    {
        m_clock->stop();
        m_engine->setPaused(true);
        m_state = Suspended;
        emit stateChanged(m_state);
    }
    redraw();
}

void ArcanoidViewWidget::onBallCrashed()
{
    m_lives--;
    emit livesChanged(m_lives);
    if (m_lives <= 0) {
        closeGame();
    }
    else {
        m_engine->resetBall();
    }
}

void ArcanoidViewWidget::onBlockHit()
{
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

void ArcanoidViewWidget::tick() {
    redraw();
//    static signed int ticks = TICKS_PER_SECOND;
//    ticks--;
//    if (ticks <= 0)
//    {
//        //m_time++;
//        //emit timeChanged(m_time);
//        ticks = TICKS_PER_SECOND;
//    }
}

void ArcanoidViewWidget::resizeEvent(QResizeEvent *ev)
{
    QPalette palette;
    palette.setBrush(backgroundRole(),QBrush(QColor("black")));
    setPalette(palette);
    setAutoFillBackground(true);

    QSize boardSize = ev->size();
    m_engine->resize(boardSize);
//    m_engine->moveTo((ev->size().width() - boardSize.width()) / 2,
//            (ev->size().height() - boardSize.height()) / 2);

    redraw();
}

void ArcanoidViewWidget::closeLevel() {
    m_clock->stop();
    m_engine->setPaused(true);
}

void ArcanoidViewWidget::newLevel() {
    m_state = Running;
    emit stateChanged(m_state);

    m_clock->start();
    m_engine->newLevel(m_level);
    m_engine->setPaused(false);

    emit livesChanged(m_lives);
    redraw();
}

void ArcanoidViewWidget::redraw()
{
    if (size().isEmpty())
        return;

//    switch (m_state)
//    {
//    case BeforeFirstGame:
//        m_engine->hide();
//        break;
//    case Running:
//        m_engine->show();
//        break;
//    default:
//        m_engine->show();
//        break;
//    }
    m_engine->redraw();
    update();
}


void ArcanoidViewWidget::onLevelCleared()
{
    if (m_state == Running)
    {
        m_state = BetweenLevels;
        closeLevel();
        m_level++;

        emit stateChanged(m_state);
        redraw();
    }

}

ArcanoidViewWidget::State ArcanoidViewWidget::state() const
{
  return m_state;
}
