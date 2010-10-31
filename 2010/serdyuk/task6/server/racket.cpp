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

    
void Racket::write(QDomElement *element) const {
    QDomElement racket;
    racket.setTagName("Racket");
    racket.setAttribute("x", QString("%1").arg(myX));
    element->appendChild(racket);
}
