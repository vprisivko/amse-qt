#include <QApplication>
#include "timers.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Timers w;
    w.show();
    return a.exec();
}
