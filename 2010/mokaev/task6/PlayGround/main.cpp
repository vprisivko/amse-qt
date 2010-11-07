#include <QApplication>
#include <QFile>

#include "ArcanoidDialog.h"

int main( int argc, char* argv[] ){
    QFile file("ipconf");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return -1;
    }
    QHostAddress ip;
    ip.setAddress( QString( file.readLine() ) );

    int port = QString(file.readLine()).toInt();
    file.close();

    QApplication app( argc, argv );
    ArcanoidDialog arcanoidDialog( ip, port, NULL );
    arcanoidDialog.show();
    return app.exec();

}

