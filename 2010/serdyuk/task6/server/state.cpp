// =====================================================================================
// 
//       Filename:  state.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  29.10.2010 18:20:52
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#include "state.h"

#include <QDomDocument>

#include <cmath>
#include <cstdlib>

#include "statehandler.h"

State::State(int width, int height, QObject *parent) : QObject(parent) {
    myCurrentState = "begin";
    mySpareBalls = 3;
    myBall = new Ball(width / 2, height / 2, rand() % 11 - 5, rand() % 11 - 5, this);
    myRacket = new Racket(width / 2, this);
    myFieldWidth = width;
    myFieldHeight = height;

    goRight = false;
    goLeft = false;
    start = false;
}

    
State::State(QString currentState, Ball *ball, Racket *racket, int spareBalls, int fieldWidth, int fieldHeight, QObject *parent) : QObject(parent) {
    myCurrentState = currentState;
    myBall = ball;
    myRacket = racket;
    mySpareBalls = spareBalls;
    myFieldWidth = fieldWidth;
    myFieldHeight = fieldHeight;
}

QString State::write() const {
    QDomDocument doc("State");
    QDomElement root = doc.createElement("State");
    doc.appendChild(root);

    QDomElement state = doc.createElement("CurrentState");
    state.setAttribute("state", myCurrentState);
    root.appendChild(state);

    QDomElement spareBalls = doc.createElement("Racket");
    spareBalls.setAttribute("count", QString("%1").arg(mySpareBalls));
    root.appendChild(spareBalls);

    QDomElement field = doc.createElement("Field");
    field.setAttribute("width", QString("%1").arg(myFieldWidth));
    field.setAttribute("height", QString("%1").arg(myFieldHeight));
    root.appendChild(field);

    myBall->write(&doc, &root);
    myRacket->write(&doc, &root);

    return doc.toString(INDENT);
}

State* State::createInstance(QXmlInputSource *source, QObject *parent) {
    QXmlSimpleReader reader;
    StateHandler handler(parent);
    reader.setContentHandler(&handler);
    reader.setErrorHandler(&handler);

    bool ok = reader.parse(source);

    if (!ok) {
        return 0;
    }
    Ball *ball = handler.getBall();
    Racket *racket = handler.getRacket();
    QString currentState = handler.getCurrentState();
    int spareBalls = handler.getSpareBalls();
    int fieldWidth = handler.getFieldWidth();
    int fieldHeight = handler.getFieldHeight();

    return new State(currentState, ball, racket, spareBalls, fieldWidth, fieldHeight, parent);
}
    
QPoint State::tick() {
    if (start) { // User pressed "start"
        if (myCurrentState == "begin") {
            myCurrentState = "run";
            myBall->setX(myFieldWidth / 2);
            myBall->setY(myFieldHeight / 2);
            myBall->initV();
        } else if (myCurrentState == "fall") {
            if (mySpareBalls > 0) {
                --mySpareBalls;
                myCurrentState = "run";
            }
            myBall->setX(myFieldWidth / 2);
            myBall->setY(myFieldHeight / 2);
            myBall->initV();
        }
        start = false;
    }

    if (myCurrentState == "begin" || myCurrentState == "fall" || myCurrentState == "gameover") {
        return QPoint(0, 0);
    }

    if (myCount % TICKS_PER_DELAY == 0) {
        if (goRight && myRacket->getX() + Racket::WIDTH < myFieldWidth) { // User pressed "left" button
            myRacket->goRight();
            goRight = false;
        }
        if (goLeft && myRacket->getX() > 0) { // User pressed "right" button
            myRacket->goLeft();
            goLeft = false;
        }
    }
    myBall->move();

    int xRadius = Ball::RADIUS;
    int yRadius = Ball::RADIUS;
    if (myBall->getX() - Ball::RADIUS < 0) {
        xRadius = myBall->getX();
    } 
    if (myBall->getX() + Ball::RADIUS > myFieldWidth) {
        xRadius = myFieldWidth - myBall->getX();
    }
    if (myBall->getX() - Ball::RADIUS < -Ball::RADIUS / 2) {
        myBall->flipV();
        myBall->setX(Ball::RADIUS / 2);
    }
    if (myBall->getX() + Ball::RADIUS > myFieldWidth + Ball::RADIUS / 2) {
        myBall->flipV();
        myBall->setX(myFieldWidth - Ball::RADIUS / 2);
    }
    if (myBall->getY() - Ball::RADIUS < Racket::HEIGHT) {
        yRadius = myBall->getY() - Racket::HEIGHT;
    }
    if (myBall->getY() + Ball::RADIUS > myFieldHeight) {
        yRadius = myFieldHeight - myBall->getY();
    }
    if (myBall->getY() - Ball::RADIUS < -Ball::RADIUS / 2) {
        myBall->flipH();
        myBall->setY(Ball::RADIUS / 2);
    }
    if (myBall->getY() + Ball::RADIUS > myFieldHeight + Ball::RADIUS / 2 + Racket::HEIGHT) {
        if (myBall->getX() > myRacket->getX() && myBall->getX() < myRacket->getX() + Racket::WIDTH) {
            myBall->flipH();
            myBall->setY(myFieldHeight - Ball::RADIUS / 2);
        } else {
            myCurrentState = "fall";
        }
    }
    return QPoint(xRadius, yRadius);
}

void State::changeState(QString state) {
    myCurrentState = state;
}
    
Ball *State::getBall() const {
    return myBall;
}
    
Racket *State::getRacket() const {
    return myRacket;
}
    
bool State::doAction(QString action) {
    if (action == "left") {
        goLeft = true;
    } else if (action == "right") {
        goRight = true;
    } else if (action == "start") {
        start = true;
    } else {
        return false;
    }
    return true;
}

QString State::getCurrentState() const {
    return myCurrentState;
}
    
int State::getFieldWidth() const {
    return myFieldWidth;
}
