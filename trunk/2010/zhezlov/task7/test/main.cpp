#include <QApplication>
#include <QTest>
#include <test1.h>

int main( int c, char** v ){

    QApplication app(c, v);
    Test1 test;
    QTest::qExec( &test );
    return app.exec();

}
