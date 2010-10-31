#include <QApplication>
#include <arkanoidserver.h>

int main( int c, char** v){

    QApplication app(c, v);

    ArkanoidServer w;

    w.show();

    return app.exec();

}

