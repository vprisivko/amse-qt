#include <QApplication>
#include <QFile>

#include "ControlDialog.h"


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
    ControlDialog ctrlDialog( ip, port, NULL );
    ctrlDialog.show();
    return app.exec();

}
