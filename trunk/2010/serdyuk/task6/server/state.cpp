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

    QDomElement state;
    state.setTagName("CurrentState");
    state.setAttribute("state", myCurrentState);
    root.appendChild(state);

    QDomElement spareBalls;
    spareBalls.setTagName("Racket");
    spareBalls.setAttribute("count", QString("%1").arg(mySpareBalls));
    root.appendChild(spareBalls);

    QDomElement field;
    field.setTagName("Field");
    field.setAttribute("width", QString("%1").arg(myFieldWidth));
    field.setAttribute("height", QString("%1").arg(myFieldHeight));
    root.appendChild(field);

    myBall->write(&root);
    myRacket->write(&root);

    return doc.toString();
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
    
void State::tick() {
    if (myCurrentState == "begin" || myCurrentState == "fall" || myCurrentState == "gameover") {
        return;
    }
    myBall->move();

    int xRadius = BALL_RADIUS;
    int yRadius = BALL_RADIUS;
    if (myBall->getX() - BALL_RADIUS < 0) {
        xRadius = myBall->getX();
    } 
    if (myBall->getX() + BALL_RADIUS > myFieldWidth) {
        xRadius = myFieldWidth - myBall->getX();
    }
    if (myBall->getX() - BALL_RADIUS < -BALL_RADIUS / 2) {
        myBall->flipV();
        myBall->setX(BALL_RADIUS / 2);
    }
    if (myBall->getX() + BALL_RADIUS > myFieldWidth + BALL_RADIUS / 2) {
        myBall->flipV();
        myBall->setX(myFieldWidth - BALL_RADIUS / 2);
    }
    if (myBall->getY() - BALL_RADIUS < 0) {
        yRadius = myBall->getY();
    }
    if (myBall->getY() + BALL_RADIUS > myFieldHeight) {
        yRadius = myFieldHeight - myBall->getY();
    }
    if (myBall->getY() - BALL_RADIUS < -BALL_RADIUS / 2) {
        myBall->flipH();
        myBall->setY(BALL_RADIUS / 2);
    }
    if (myBall->getY() + BALL_RADIUS > myFieldHeight + BALL_RADIUS / 2) {
        myBall->flipH();
        myBall->setY(myFieldHeight - BALL_RADIUS / 2);
    }
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
