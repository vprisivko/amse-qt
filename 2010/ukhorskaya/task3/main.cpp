#include <QtGui/QApplication>
#include "Widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w(NULL);
    w.show();
    return a.exec();
}
