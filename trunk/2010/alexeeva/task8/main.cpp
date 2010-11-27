#include "calccreator.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalcCreator w;
    w.show();
    return a.exec();
}
