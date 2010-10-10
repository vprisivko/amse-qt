#include <QApplication>
#include "BallDialog.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	BallDialog mainDialog(0, 100, 100, 3, 5, 10, 10, 50);
	mainDialog.show();
	return app.exec();
}
