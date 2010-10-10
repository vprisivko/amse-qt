#include <QApplication>
#include <Calculator.h>


int main ( int c, char** v ){

	QApplication a(c, v);
	Calculator w;
	w.show();
	return a.exec();

}

