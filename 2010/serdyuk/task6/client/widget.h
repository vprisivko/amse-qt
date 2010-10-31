// =====================================================================================
// 
//       Filename:  widget.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  31.10.2010 23:29:07
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QUdpSocket>

class Widget : public QWidget {
    Q_OBJECT;
public:
    Widget(QString port, QString address, QWidget *parent = 0);

private:
    QPushButton *myLeftButton;
    QPushButton *myRightButton;
    QPushButton *myStartButton;
    QUdpSocket *mySocket;

};

#endif   // ----- #ifndef WIDGET_H -----

