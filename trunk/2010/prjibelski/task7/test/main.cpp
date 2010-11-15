#include <QApplication>
#include <QTest>
#include "TestTimer.h"

int main(int c, char* v[]){
    QApplication app(c,v);
    TestTimer test;
    QTest::qExec(&test);
    app.exec();
}
