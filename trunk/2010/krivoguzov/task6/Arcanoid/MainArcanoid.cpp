#include <Arcanoid.h>
#include <QApplication>

int main (int argc, char** argv){
    if(argc == 4){
            QApplication app(argc,argv);
            Arcanoid mainWindow(argv[1],QString(argv[2]).toInt(),QString(argv[3]).toInt());
            mainWindow.show();
            app.exec();
        }
    else{
        qDebug() << "Please specify a destination IP, destination port, and port to listen for incoming data. Example:";
        qDebug() << "./task6 192.168.0.1 49753 45721";
    }


}

