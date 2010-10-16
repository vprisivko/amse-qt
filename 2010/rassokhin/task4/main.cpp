#include <QtGui/QApplication>
#include "calculatemainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalculateMainWindow w;
    w.show();
    return a.exec();
}
