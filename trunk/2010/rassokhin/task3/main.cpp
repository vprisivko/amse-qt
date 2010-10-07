#include <QtGui/QApplication>
#include "movingballdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MovingBallDialog w;
    w.show();
    return a.exec();
}
