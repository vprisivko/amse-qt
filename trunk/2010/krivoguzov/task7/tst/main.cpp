#include <QApplication>
#include <QTest>
#include "MyTest.h"

int main(int argc, char **argv){
    QApplication app(argc,argv);
    MyTest testObject;
    QTest::qExec(&testObject);
    return 0;
}
