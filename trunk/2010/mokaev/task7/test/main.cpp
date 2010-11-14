#include <QApplication>
#include "test.h"

int main( int argc, char* argv[] ){
        QApplication app( argc, argv );
        MyTest test;
        QTest :: qExec( &test );
        return 0;
}
