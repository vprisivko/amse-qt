#include <QtGui/QApplication>
#include "Calculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator calc;
    calc.show();
    return a.exec();
}
