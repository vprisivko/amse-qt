#include <iostream>
#include <QString>
#include <QApplication>
#include <QMessageBox>
#include "udpchat.h"


int usage()
{
	QString mess = "Program options run: prog_name [port]";
	QMessageBox::warning(0, "Error", mess);
	std::cout << mess.toStdString() << std::endl;
	return -1;
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	UdpChat *w = 0;
	if(argc == 2) {
		bool ok = false;
		int port = QString(argv[1]).toInt(&ok);
		if(!ok) return usage();
		w = new UdpChat(0, port);
	} else if(argc < 2) {
		w = new UdpChat();
	} else {
		return usage();
	}
	w->show();
	return app.exec();
}
