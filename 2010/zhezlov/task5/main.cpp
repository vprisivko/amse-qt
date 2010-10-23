#include <QApplication>
#include <udpchat.h>


int main ( int c, char** v ){

	QApplication a(c, v);
        UdpChat w;
	w.show();
	return a.exec();

}

