#include <QtGui/QApplication>
#include "MyDialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyDialog w;
    w.setWindowTitle("Mega Timer");
    w.show();
    return a.exec();
}
