// =====================================================================================
// 
//       Filename:  ball.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  31.10.2010 19:35:20
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#include "ball.h"

Ball::Ball(int x, int y, int vx, int vy, QObject *parent) : QObject(parent) {
    myX = x;
    myY = y;

    myVx = vx;
    myVy = vy;
}

void Ball::write(QDomElement *element) const {
    QDomElement ball;
    ball.setTagName("Ball");
    ball.setAttribute("x", QString("%1").arg(myX));
    ball.setAttribute("y", QString("%1").arg(myY));
    ball.setAttribute("vx", QString("%1").arg(myVx));
    ball.setAttribute("vy", QString("%1").arg(myVy));
    element->appendChild(ball);
}
    
int Ball::getX() const {
    return myX;
}
    
int Ball::getY() const {
    return myY;
}

void Ball::move() {
    myX += myVx;
    myY += myVy;
}
    
void Ball::flipV() {
    myVx = -myVx;
}
    
void Ball::flipH() {
    myVy = -myVy;
}
    
void Ball::setX(int x) {
    myX = x;
}
    
void Ball::setY(int y) {
    myY = y;
}
