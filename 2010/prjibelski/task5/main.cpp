#include <QtGui/QApplication>
#include <iostream>

#include "chatdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    try {
        ChatDialog chatDialog( QString( argv[1]).toInt() );
        chatDialog.show();
        return a.exec();

    }
    catch ( std::exception ) {
        std::cerr << "Probably port is busy. Terminating now...\n";
        return -1;
    }
}
