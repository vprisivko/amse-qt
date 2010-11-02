#include <QApplication>
#include <QHostAddress>
#include <QString>
#include "RemoteControlDialog.h"

int main(int argc, char *argv[])
{
    if (argc != 5) {
        return 1;
    }
    QApplication app(argc, argv);
    RemoteControlDialog dialog(QHostAddress(QString(argv[1])), QString(argv[2]).toInt(), QHostAddress(QString(argv[3])), QString(argv[4]).toInt());
    dialog.show();
    return app.exec();
}
