// =====================================================================================
// 
//       Filename:  ball.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  29.10.2010 18:15:38
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QDomDocument>

class Ball : public QObject {
private:
    int myX;
    int myY;

    int myVx;
    int myVy;

public:
    static const int RADIUS = 20;
    Ball(int x, int y, int vx, int vy, QObject *parent = 0);

    void write(QDomDocument *doc, QDomElement *element) const;

    void move();
    void flipV();
    void flipH();
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
    void initV();
};

#endif   // ----- #ifndef BALL_H -----

