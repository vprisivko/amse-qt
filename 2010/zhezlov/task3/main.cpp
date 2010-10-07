#include <QApplication>
#include <Ballolo.h>


int main ( int c, char** v ){

	QApplication a(c, v);
	Ballolo w;
	w.show();
	return a.exec();

}

