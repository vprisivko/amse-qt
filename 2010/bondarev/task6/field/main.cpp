#include <QApplication>
#include <QString>
#include "arcanoid.h"

int main(int c, char *v[])
{
    QApplication a(c, v);
    if (c == 3) {
        Arcanoid w(QHostAddress(QString(v[1])), QString(v[2]).toInt());
        w.show();
        return a.exec();
    } else {
        printf("Error!\nUsage: >>fieldForGame <ip> <port>\n");
        return -1;
    }
}
