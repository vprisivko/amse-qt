#include <QApplication>
#include <QString>
#include <iostream>

#include "ControlDialog.h"

int main(int argc, char** argv) {
        if(argc < 2){
            std::cout << "Usage: control <port>" << std::endl;
           return 0;
        }

        int result = 0;
        try {
            QApplication app(argc,argv);
            quint16 port = QString(argv[1]).toUInt();
            ControlDialog dialog(port);
            dialog.show();
            result =  app.exec();
        }

        catch ( std::exception ) {
            std::cout << "Can't use this port!" << std::endl;
            result = -1;
        }
        return result;
}

