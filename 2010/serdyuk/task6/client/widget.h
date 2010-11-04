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
#include <QKeyEvent>

class Widget : public QWidget {
    Q_OBJECT;
public:
    Widget(QString address, QString port, QWidget *parent = 0);

    void keyPressEvent(QKeyEvent *e);

private:
    QPushButton *myLeftButton;
    QPushButton *myRightButton;
    QPushButton *myStartButton;
    QUdpSocket *mySocket;

    QHostAddress myAddress;
    int myPort;
    
private slots:
    void readPendingDatagrams();
    void goRight();
    void goLeft();
    void start();
};

#endif   // ----- #ifndef WIDGET_H -----

