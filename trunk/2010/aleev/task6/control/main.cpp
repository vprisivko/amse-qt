#include <QApplication>
#include <QString>
#include <iostream>

#include "Control.h"

int main(int argc, char** argv) {
        if(argc < 2){
            std::cout << "Wrong number of arguments\nUsage: ./Control <port>" << std::endl;
           return 0;
        }

        int result = 0;
        try {
            QApplication app(argc,argv);
            quint16 port = QString(argv[1]).toUInt();
            ControlDialog cd(port);
            cd.show();
            result =  app.exec();
        }
        catch (std::exception) {
            std::cout << "Can't use this port, try another one..." << std::endl;
            result = -1;
        }

        return result;
}

