#include "Chat.h"
#include <QApplication>

int main(int n, char **v) {
    QApplication a(n, v);
    if (n > 1) {
        Chat l(QString(v[1]).toInt());
        l.show();
        return a.exec();
    }
}
