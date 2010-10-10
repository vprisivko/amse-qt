#include <QApplication>
#include "LoggerWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName("AMSE-Qt");
    QApplication::setOrganizationDomain("korgov.amse.ru");
    QApplication::setApplicationName("CalcLogger");
	LoggerWindow w;

	w.show();
    return a.exec();
}
