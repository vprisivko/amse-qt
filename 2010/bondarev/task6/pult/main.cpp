#include <QApplication>
#include <stdio.h>
#include "pult.h"

int main(int c, char *v[]) {
    QApplication a(c, v);
    if (c == 5) {
        Pult w(v[1], QString(v[2]).toInt(), v[3], QString(v[4]).toInt());
        w.show();
        return a.exec();
    } else {
        printf("Error!\nUsage: >>pultForGame <your ip> <your port> <to ip> <to port>\n");
        return -1;
    }
}
