#include <QApplication>
#include "Pult.h"
#include <QFile>
#include <QHostAddress>

int main(int n, char **v) {
    QApplication a(n, v);
    QFile file("Pult/ipconfig");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 1;
    QHostAddress ip;
    qint16 port;
    ip.setAddress(QString(file.readLine()));
    port = QString(file.readLine()).toInt();
    file.close();
    Pult p(ip, port);
    p.show();
    return a.exec();
}
