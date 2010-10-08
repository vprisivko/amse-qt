#include <QApplication>
#include "BallDialog.h"

int main(int argc, char** argv) {
	QApplication app(argc,argv);
	
	BallDialog ballDialog;
	ballDialog.show();
	
	return app.exec();
} 
