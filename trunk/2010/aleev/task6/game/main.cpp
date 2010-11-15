#include <QApplication>
#include <QString>
#include <iostream>

#include "Game.h"

int main(int argc, char** argv) {
    if(argc < 2){
        std::cout << "Wrong nimber of arguments\nUsage: ./Game <port>" << std::endl;
       return 0;
    }

    int result = 0;
    try {
        QApplication app(argc,argv);
        quint16 port = QString(argv[1]).toUInt();
        GameDialog gd(port);
        gd.show();
        result =  app.exec();
    }
    catch ( std::exception ) {
        std::cout << "Can't use this port, try another one..." << std::endl;
        result = -1;
    }

    return result;
} 
