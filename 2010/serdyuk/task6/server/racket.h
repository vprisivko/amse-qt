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
#include <QDomDocument>

class Racket : public QObject {
private:
    int myX;

public:
    static const int WIDTH = 80;
    static const int HEIGHT = 5;
    Racket(int x, QObject *parent = 0);

    void goRight();
    void goLeft();

    int getX() const;

    void write(QDomDocument *doc, QDomElement *element) const;
};

#endif   // ----- #ifndef RACKET_H -----

