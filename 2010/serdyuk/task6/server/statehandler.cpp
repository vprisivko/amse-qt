// =====================================================================================
// 
//       Filename:  statehandler.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  31.10.2010 19:50:58
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#include "statehandler.h"

StateHandler::StateHandler(QObject *parent) {
    myBall = 0;
    myRacket = 0;
    myParent = parent;
}
    
bool StateHandler::startElement(const QString &, const QString &localName, const QString &, const QXmlAttributes &atts) {
    if (localName == "Ball") {
        QString x = atts.value("x");
        QString y = atts.value("y");
        QString vx = atts.value("vx");
        QString vy = atts.value("vy");

        if (myBall == 0) {
            myBall = new Ball(x.toInt(), y.toInt(), vx.toInt(), vy.toInt(), myParent);
        }
    } else if (localName == "Racket") {
        QString x = atts.value("x");
        myRacket = new Racket(x.toInt(), myParent);
    } else if (localName =="SpareBalls") {
        QString count = atts.value("count");
        mySpareBalls = count.toInt();
    } else if (localName == "CurrentState") {
        myCurrentState = atts.value("state");
    } else if (localName == "Field") {
        QString width = atts.value("width");
        QString height = atts.value("height");
        myFieldWidth = width.toInt();
        myFieldHeight = width.toInt();
    }
    return true;
}

    
Ball *StateHandler::getBall() const {
    return myBall;
}
    
Racket *StateHandler::getRacket() const {
    return myRacket;
}
    
int StateHandler::getSpareBalls() const {
    return mySpareBalls;
}
    
QString StateHandler::getCurrentState() const {
    return myCurrentState;
}

int StateHandler::getFieldWidth() const {
    return myFieldWidth;
}
    
int StateHandler::getFieldHeight() const {
    return myFieldHeight;
}
