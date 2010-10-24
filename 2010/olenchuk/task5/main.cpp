#include "ChatDialog.h"
#include <QApplication>
#include <QMessageBox>

int main(int argv, char *argc[]) {
	QApplication app(argv, argc);
	if (argv < 2) {
		return 1;
	}
	int port = QString(argc[1]).toInt();
	if((port<0) || (port>65535)){
		QMessageBox::information(0, "Chat", "Try again in the range 0....65535");
		return 1;
	}	
	ChatDialog chat;
	if(!chat.initSocket(port)) {
		QMessageBox::critical(0, "Chat", "Port " + QString::number(port) + " is busy");
 		return 1;
	}
	chat.show();

	return app.exec();
}
