#include<QApplication>
#include<QTest>
#include"Test1.h"

int main(int c, char* v[]){
    QApplication app(c,v);
    Test1 test;
    QTest::qExec(&test);
    app.exec();
}
