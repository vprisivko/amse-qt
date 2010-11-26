#include <QtGui/QApplication>
#include "threadedtimers.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ThreadedTimers w;
    w.show();

    return a.exec();
}
