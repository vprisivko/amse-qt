#include <QApplication>
#include <stdio.h>
#include "dialog.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    if (argc > 1) {
        Dialog w(QString(argv[1]).toInt());
        w.show();
        return a.exec();
    } else {
        printf("Usage: >>task5 <port>\n");
    }
}
