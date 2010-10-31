#include <QApplication>
#include "arkanoidclient.h"

int main( int c, char** v){
    QApplication app(c, v);
    ArkanoidClient w;
    w.show();
    return app.exec();
}
