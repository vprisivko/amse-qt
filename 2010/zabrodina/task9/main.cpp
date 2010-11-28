#include<stdio.h>
#include <QtGui/QApplication>
#include<QDialog>
#include"MyDialog.h"

int main(int argc, char *argv[]) {
QApplication app(argc, argv);
MyDialog dial;
dial.show();
return app.exec();
}

