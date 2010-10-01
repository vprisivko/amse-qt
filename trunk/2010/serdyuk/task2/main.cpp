// =====================================================================================
// 
//       Filename:  main.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  29.09.2010 22:31:17
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#include <QApplication>

#include "dialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Dialog d;
    d.show();
    return app.exec();
}

