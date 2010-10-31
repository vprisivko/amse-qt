// =====================================================================================
// 
//       Filename:  mainwidget.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05.10.2010 22:20:39
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QTimerEvent>

#include <QUdpSocket>

#include "state.h"

class Widget : public QWidget {
    Q_OBJECT;
public:
    Widget(QWidget *p = 0);

    void paintEvent(QPaintEvent *e);
    void timerEvent(QTimerEvent *e);

private:
    State *myState;
    QUdpSocket *mySocket;
    int myPort;
};

#endif   // ----- #ifndef MAINWIDGET_H -----

