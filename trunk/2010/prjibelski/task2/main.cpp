#include <QtGui/QApplication>
#include<QDialog>
/*#include<QPushButton>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLineEdit>
#include<QComboBox>
#include<QLabel>
*/
#include"TimerDialog.h"

int main( int argc, char ** argv ) {
	QApplication app( argc, argv );
	TimerDialog timerDialog;
	timerDialog.show();
	return app.exec();
}
