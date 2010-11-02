#include <QApplication>
#include <QHostAddress>
#include <QString>
#include "BallDialog.h"

int main(int argc, char *argv[])
{
    if (argc != 5) {
        return 1;
    }
    QApplication app(argc, argv);
    BallDialog dialog(QHostAddress(QString(argv[1])), QString(argv[2]).toInt(), QHostAddress(QString(argv[3])), QString(argv[4]).toInt(), 3, 5, 10, 10, 50);
    dialog.show();
    return app.exec();
}
