#include <QApplication>
#include "LogWindow.h"

int main( int argc, char* argv[] ){
	QApplication app( argc, argv );
	
	LogWindow logWindow;
	logWindow.show();
	
	return app.exec();
}
