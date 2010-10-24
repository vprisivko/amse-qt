#include <QApplication>
#include <iostream>

#include "ChatDialog.h"

int main(int c, char **v) {
	QApplication app(c, v);

	if (c != 2) {
		std::cerr << "Usage: " << v[0] << " <port>\n";
		return -1;
	}

	ChatDialog chat(QString(v[1]).toUInt());
	chat.show();
	return app.exec();
}
