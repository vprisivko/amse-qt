// =====================================================================================
// 
//       Filename:  test.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  14.11.2010 21:34:30
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#ifndef TEST_H
#define TEST_H

#include <QObject>

#include "../src/dialog.h"

class Test : public QObject {
    Q_OBJECT;
private:
    Dialog *myDialog;

public:
    Test(QObject *parent = 0);
    ~Test();

private slots:
    void testFirstSet();
    void testSecondSet();
    void testFirstTimer();
    void testSecondTimer();
    void testStopFirst();
    void testStopSecond();
};

#endif   // ----- #ifndef TEST_H -----

