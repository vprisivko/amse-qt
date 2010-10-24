#include <QtGui/QApplication>
#include "udpchatdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(argc < 2){
        printf("Help: Enter port's number as a command line argument.\n");
        return 0;
    }
    UdpChatDialog w(atoi(argv[1]));
    w.show();
    return a.exec();
}
