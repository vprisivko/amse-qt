#include <QtGui/QApplication>
#include <QtGui/QMessageBox>

#include "clientmainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
//    bool showHelp = false;
//    if(argc < 2) showHelp = true;
//    bool convRes;
//    int port = QString(argv[1]).toInt(&convRes);
//    if(!convRes || (port<0) || (port>65535)) showHelp = true;
//
//    if (showHelp) {
//        //QMessageBox::information(0,"Simple UDP Chat","Please, run programm with port as first parameter");
//        return 1;
//    }

    ClientMainWindow w;

//    if(!w.startUdpListener(port)) {
//        QMessageBox::critical(0, "Simple UDP Chat",
//                "Cannot create server on port" + QString::number(port));
//        return 1;
//    }

    w.show();
    w.startUdpListener(12000,17000);

    return a.exec();
}
