#include<QApplication>
#include<QDialog>
#include"MyMainWindow.h"

int main(int c, char *v[]) {
    QApplication app(c,v);
    MyMainWindow mw;
    mw.show();
    app.exec();
}
