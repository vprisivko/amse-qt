#include <QApplication>
#include <Ballolo.h>


void addField( char* fieldName, QLayout* l );


int main ( int c, char** v ){

	QApplication a(c, v);
	Ballolo w;
	w.show();
	return a.exec();

}

