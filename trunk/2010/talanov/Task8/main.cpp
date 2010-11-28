#include <QtGui/QApplication>
#include "calculatorlogmw.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalculatorLogMW w;
    w.show();

    return a.exec();
}
