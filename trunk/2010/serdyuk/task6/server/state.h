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
#include <QPoint>

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

    bool goRight;
    bool goLeft;
    bool start;

    int myCount;
public:
    static const int INDENT = 4;
    static const int TICKS_PER_DELAY = 10; // Frequency user can perform actions
    
    State(int width, int height, QObject *parent = 0);

    State(QString currentState, Ball *ball, Racket *racket, int spareBalls, int fieldWidth, int fieldHeight, QObject *parent = 0);

    static State* createInstance(QXmlInputSource *source, QObject *parent);
    QString write() const;

    QPoint tick();

    void changeState(QString state);
    Ball *getBall() const;
    Racket *getRacket() const;
    QString getCurrentState() const;
    int getFieldWidth() const;

    bool doAction(QString action);
};

#endif   // ----- #ifndef STATE_H -----

