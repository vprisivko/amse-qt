#include <QApplication>
#include "Table.h"
#include "Pult.h"

int main(int n, char **v) {
    QApplication a(n, v);
    Table t(2152);
    Pult p(2154);
    t.show();
    p.show();
    return a.exec();
}
