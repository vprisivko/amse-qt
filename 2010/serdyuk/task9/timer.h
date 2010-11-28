// =====================================================================================
// 
//       Filename:  timer.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  28.11.2010 13:07:24
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#ifndef TIMER_H
#define TIMER_H

#include <QThread>
#include <QMutex>

class Timer : public QThread {
    Q_OBJECT;
private:
    int *myVariable;
    QMutex *myMutex;
    int myInterval;
public:
    Timer(int *variable, QMutex *mutex, int interval, QObject *parent = 0);
    void run();
};

#endif   // ----- #ifndef TIMER_H -----

