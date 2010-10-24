#include "udpchat.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(argc < 2){
        qDebug() << "Required parameter <port> is missing!";
        return 0;
    }
    else if(QString(argv[1]).toUInt() > 65535){
        qDebug() << "Port must be from 0 to 65535";
        return 0;
    }
    UDPChat * w = new UDPChat(QString(argv[1]).toUInt());
    w->show();
    return a.exec();
}
