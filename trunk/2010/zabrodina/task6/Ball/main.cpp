#include <QtGui/QApplication>
#include<QFile>
#include "BallDial.h"

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   QFile fin("ip_port.txt");
   if (!fin.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;
   QHostAddress ip;
   qint16 port;
   ip.setAddress(QString(fin.readLine()));
   port = QString(fin.readLine()).toInt();
   fin.close();
   BallDial w(ip,port);
   w.show();
   return a.exec();

}
