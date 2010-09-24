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

int main(int argc, char** argv) {
	QApplication app(argc,argv);
	QDialog d;

	QVBoxLayout* mainLayout = new QVBoxLayout();
	QHBoxLayout* lay = 0;
	
	d.setLayout(mainLayout);
		
	mainLayout->addWidget( new QLabel("<b>Your personal visit card</b>") );
	
	lay = new QHBoxLayout();
	lay->addWidget( new QLabel("Name:") );
	lay->addWidget( new QLineEdit("enter your name") );
	mainLayout->addLayout(lay);
	
	lay = new QHBoxLayout();
	lay->addWidget( new QLabel("Enter your password:") );
	QLineEdit* linePswd = new QLineEdit("password");
	linePswd->setEchoMode(QLineEdit::Password);
	lay->addWidget(linePswd);
	mainLayout->addLayout(lay);
	
	mainLayout->addWidget( new QLabel("Tell smth about yourself") );
	mainLayout->addWidget( new QTextEdit("something") );
	
	lay = new QHBoxLayout();
	lay->addWidget( new QLabel("Enter your growth") );
	lay->addWidget( new QSpinBox() );
	mainLayout->addLayout(lay);
	
	lay = new QHBoxLayout();
	lay->addWidget( new QLabel("Your birthday?") );
	lay->addWidget( new QDateTimeEdit(QDateTime::currentDateTime()) );
	mainLayout->addLayout(lay);
	
	lay = new QHBoxLayout();
	lay->addWidget( new QLabel("Your favourite color?") );
	QComboBox* cbFavColors = new QComboBox();
	QStringList lst;
	lst << "Red" << "Blue" << "Green" << "Purple";
	cbFavColors->addItems(lst);
	lay->addWidget( cbFavColors );
	mainLayout->addLayout(lay);
	
	QPushButton* btnExit = new QPushButton("Good bye!");	
	mainLayout->addWidget(btnExit);

	QObject::connect( btnExit, SIGNAL(clicked()), qApp, SLOT(quit()));
	d.show();
	return app.exec();
} 
