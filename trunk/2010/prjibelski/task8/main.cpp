#include <QtGui/QApplication>
#include "calclog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalcLog w;
    w.show();

    return a.exec();
}
