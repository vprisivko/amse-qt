#include <QApplication>
#include "ChatDialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	
    if(argc < 2){
        qDebug() << "Usage: task5 <port>";
        return 0;
    }
    else if(QString(argv[1]).toUInt() > 65535){
        qDebug() << "Error: port must be from 0 to 65535";
        return 0;
    }

    ChatDialog *d = new ChatDialog(QString(argv[1]).toUInt());
    d->show();
    return a.exec();
}
