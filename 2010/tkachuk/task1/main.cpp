#include <QApplication>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QSpinBox>
#include <QDateTimeEdit>
#include <QComboBox>

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	QDialog myDialog;

	QVBoxLayout* mainLayout = new QVBoxLayout();
	QHBoxLayout* lay = NULL;
	
	myDialog.setLayout(mainLayout);
	
	lay = new QHBoxLayout();
	lay->addWidget(new QLabel("Name:"));
	lay->addWidget(new QLineEdit("enter your name"));
	mainLayout->addLayout(lay);

	lay = new QHBoxLayout();
	lay->addWidget(new QLabel("Surname:"));
	lay->addWidget(new QLineEdit("enter your surname"));
	mainLayout->addLayout(lay);
	
	QPushButton *extBtn= new QPushButton("Quit");
	mainLayout->addWidget(extBtn);
	QObject::connect(extBtn, SIGNAL(clicked()), qApp, SLOT(quit()));
	myDialog.show();

	return app.exec();
} 
