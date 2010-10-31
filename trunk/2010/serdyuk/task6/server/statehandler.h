// =====================================================================================
// 
//       Filename:  statehandler.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  31.10.2010 19:44:53
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#ifndef STATEHANDLER_H
#define STATEHANDLER_H

#include <QXmlDefaultHandler>

#include "ball.h"
#include "racket.h"

class StateHandler : public QXmlDefaultHandler {
private:
    Ball *myBall;
    Racket *myRacket;
    QString myCurrentState;
    int mySpareBalls;
    int myFieldHeight;
    int myFieldWidth;
    QObject *myParent;

public:
    StateHandler(QObject *parent = 0);
    bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
    Ball *getBall() const;
    Racket *getRacket() const;
    int getSpareBalls() const;
    QString getCurrentState() const;
    int getFieldWidth() const;
    int getFieldHeight() const;
};

#endif   // ----- #ifndef STATEHANDLER_H -----

