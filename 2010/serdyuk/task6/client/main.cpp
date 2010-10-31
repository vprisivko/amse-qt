// =====================================================================================
// 
//       Filename:  main.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  27.10.2010 11:55:11
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#include <QApplication>
#include <QString>

#include "widget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    if (argc < 3) {
        return 1;
    }
    Widget w(QString("%1").arg(argv[1]), QString("%1").arg(argv[2]));
    w.show();
    return app.exec();
}

