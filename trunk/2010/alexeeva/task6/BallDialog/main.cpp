#include "balldialog.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
	QFile config("ipconfig");
	if (!config.open(QIODevice::ReadOnly | QIODevice::Text))
		return -1;

    QApplication a(argc, argv);
    BallDialog * w = new BallDialog(QHostAddress(QString(config.readLine())),
    		QString(config.readLine()).toUInt());

	config.close();
	w->show();
    return a.exec();
}
