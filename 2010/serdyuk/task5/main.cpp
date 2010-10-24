#include <QtGui/QApplication>
#include <QString>
#include "widget.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        return 1;
    }
    QApplication a(argc, argv);

    Widget w(QString(argv[1]).toInt());
    w.show();

    return a.exec();
}
