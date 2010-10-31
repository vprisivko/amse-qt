#include "Arconoid.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    qsrand(QTime::currentTime().msec());
    QApplication a(argc, argv);
    Arconoid w;
    w.show();
    return a.exec();
}
