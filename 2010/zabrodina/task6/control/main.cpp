#include <QtGui/QApplication>
#include "control.h"
#include<QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile fin("ip_port.txt");
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text))
         return -1;
    QHostAddress destip;
    qint16 destport;
    qint16 myport;
    destip.setAddress(QString(fin.readLine()));
    destport = QString(fin.readLine()).toInt();
    myport = QString(fin.readLine()).toInt();
    fin.close();
    Control w(destip,destport,myport);
    w.show();
    return a.exec();
}
