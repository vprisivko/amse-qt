#include <QApplication>
#include <QDebug>
#include "MyChat.h"

int main(int argc, char** argv){
    if(argc == 2){
        QApplication app(argc,argv);
        MyChat myMainChat(QString(argv[1]).toInt());
        myMainChat.show();
        app.exec();
    }
    else{
        qDebug() << "Please specify a port number. Example:";
        qDebug() << "./task5 49753";
    }
}
