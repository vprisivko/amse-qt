#include <QtGui/QApplication>
#include <QtGui/QMessageBox>

#include "clientmainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ClientMainWindow w;

    w.show();
    w.startUdpListener(12000,17000);

    return a.exec();
}
