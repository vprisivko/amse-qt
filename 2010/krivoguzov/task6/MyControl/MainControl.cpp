#include <QApplication>
#include <QDebug>
#include "MyControl.h"

int main(int argc, char** argv){
    if(argc == 4){
            QApplication app(argc,argv);
            MyControl myMainControl(argv[1],QString(argv[2]).toInt(),QString(argv[3]).toInt());
            myMainControl.show();
            app.exec();
        }
    else{
        qDebug() << "Please specify a destination IP, destination port, and port to listen for incoming data. Example:";
        qDebug() << "./task6 192.168.0.2 45721 49753";
    }
}

