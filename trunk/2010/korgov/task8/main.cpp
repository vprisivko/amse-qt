#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName("AMSE-Qt");
    QApplication::setOrganizationDomain("korgov.amse.ru");
    QApplication::setApplicationName("CalcLogger");
    MainWindow w;
    w.show();

    return a.exec();
}
