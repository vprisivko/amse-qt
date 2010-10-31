// =====================================================================================
// 
//       Filename:  state.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  27.10.2010 12:06:57
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#ifndef STATE_H
#define STATE_H

#include <QString>
#include <QObject>
#include <QXmlInputSource>

#include "racket.h"
#include "ball.h"

class State : public QObject {
private:
    QString myCurrentState;
    Ball *myBall;
    Racket *myRacket;
    int mySpareBalls;
    int myFieldWidth;
    int myFieldHeight;
public:
    const static int BALL_RADIUS = 20;

    State(int width, int height, QObject *parent = 0);

    State(QString currentState, Ball *ball, Racket *racket, int spareBalls, int fieldWidth, int fieldHeight, QObject *parent = 0);

    static State* createInstance(QXmlInputSource *source, QObject *parent);
    QString write() const;

    void tick();

    void changeState(QString state);
    Ball *getBall() const;
    Racket *getRacket() const;
};

#endif   // ----- #ifndef STATE_H -----

