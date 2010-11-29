#include <QApplication>
#include <QTest>
#include "Test.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    Test test;
    QTest::qExec(&test);
    app.exec();
}
