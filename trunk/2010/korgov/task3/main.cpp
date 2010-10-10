#include <QApplication>
#include <QDateTime>
#include "BallWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	qsrand(QDateTime::currentDateTime().toTime_t());
    BallWidget ballDialog;
	ballDialog.show();
    return a.exec();
}
