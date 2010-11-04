// =====================================================================================
// 
//       Filename:  main.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05.10.2010 22:31:40
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#include "mainwidget.h"

#include <QApplication>
#include <QString>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Widget w;
    w.show();
    return app.exec();
}

