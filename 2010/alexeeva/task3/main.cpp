#include "balldialog.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BallDialog w;
    w.show();
    return a.exec();
}
