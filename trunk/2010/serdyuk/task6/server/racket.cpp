// =====================================================================================
// 
//       Filename:  racket.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  31.10.2010 19:32:38
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#include "racket.h"

Racket::Racket(int x, QObject *parent) : QObject(parent) {
    myX = x;
}

    
void Racket::write(QDomDocument *doc, QDomElement *element) const {
    QDomElement racket = doc->createElement("Racket");
    racket.setAttribute("x", QString("%1").arg(myX));
    element->appendChild(racket);
}
    
void Racket::goRight() {
    myX += 20;
}
    
void Racket::goLeft() {
    myX -= 20;
}
    
int Racket::getX() const {
    return myX;
}
