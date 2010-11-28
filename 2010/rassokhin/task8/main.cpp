#include <QtGui/QApplication>
#include "calculatormainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalculatorMainWindow w;
    w.show();
    return a.exec();
}
