#include <QApplication>
#include "Table.h"
#include <QFile>
#include <QHostAddress>

int main(int n, char **v) {
    QApplication a(n, v);
    QFile file("Table/ipconfig");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 1;
    QHostAddress ip;
    qint16 port;
    ip.setAddress(QString(file.readLine()));
    port = QString(file.readLine()).toInt();
    file.close();
    Table t(ip, port);
    t.show();
    return a.exec();
}
