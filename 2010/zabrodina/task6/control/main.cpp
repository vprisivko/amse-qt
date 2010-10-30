#include <QtGui/QApplication>
#include "control.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Control w(12345,0);
    w.show();
    return a.exec();
}
