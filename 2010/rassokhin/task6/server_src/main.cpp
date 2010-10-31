#include <QtGui/QApplication>
#include <QtGui/QMessageBox>

#include "servermainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    bool showHelp = false;
    if(argc < 2) showHelp = true;
    bool convRes;
    int port = QString(argv[1]).toInt(&convRes);
    if(!convRes || (port<0) || (port>65535)) showHelp = true;

    if (showHelp) {
        QMessageBox::information(0, "Arcanoid Server", "Please, run programm with port as first parameter");
        return 1;
    }

    ServerMainWindow w;

    if(!w.startUdpListener(port,port+1000)) {
        QMessageBox::critical(0, "Arcanoid Server",
                "Cannot create server on port" + QString::number(port));
        return 1;
    }

    w.show();

    return a.exec();
}
