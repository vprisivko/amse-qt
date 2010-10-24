#include <QApplication>
#include "ChatDialog.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	if (argc < 2) {
		qDebug() << "Usage: task5 <port>";
		return 0;
	}

	int result = 0;
	try {		
		ChatDialog *dialog = new ChatDialog(QString(argv[1]).toUInt());		
		dialog->show();
		result = app.exec();
	}
	catch (std::exception) {
		qDebug() << "The port is unavailable or incorrect.";
		return 1;
	}

	return result;
}
