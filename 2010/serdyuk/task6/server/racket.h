// =====================================================================================
// 
//       Filename:  racket.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  29.10.2010 18:16:32
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#ifndef RACKET_H
#define RACKET_H

#include <QObject>
#include <QDomElement>

class Racket : public QObject {
private:
    int myX;

public:
    Racket(int x, QObject *parent = 0);

    void write(QDomElement *element) const;
};

#endif   // ----- #ifndef RACKET_H -----

