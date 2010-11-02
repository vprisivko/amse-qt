#include "Control.h"
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
	QString ipAddress = argc[2];	
	Control control;
	if(!control.initSocket(port, ipAddress)) {
		QMessageBox::critical(0, "Chat", "Port " + QString::number(port) + " is busy");
 		return 1;
	}
	control.show();

	return app.exec();
}
