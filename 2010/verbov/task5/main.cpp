#include <QApplication>
#include <iostream>
#include "ChatDialog.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	if (argc != 2) {
		std::cout << "Usage: ./task5 port" << std::endl;
		return 1;
	}
	ChatDialog dialog(QString(argv[1]).toUInt());
	dialog.show();
	return app.exec();
}
