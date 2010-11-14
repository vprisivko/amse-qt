// =====================================================================================
// 
//       Filename:  main.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  14.11.2010 21:39:10
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#include <QApplication>
#include <QTest>

#include "test.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Test *test = new Test();
    QTest::qExec(test);
    return 0;
}

