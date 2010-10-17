#include "main_window.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalculatorLogMW w;
    w.show();
    return a.exec();
}
