#include "Chat.h"
#include <QString>
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    if (argc < 2) {
        qDebug() << "Parameter <portNumber> missed";
        return 0;
    }
    else if (QString(argv[1]).toUInt() > 65535) {
        qDebug() << "Specify port between 0 and 65535";
        return 0;
    }
    Chat *chat = new Chat(QString(argv[1]).toUInt());
    chat->show();
    return app.exec();
}
