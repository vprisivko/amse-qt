#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>


void addField( char* fieldName, QLayout* l );


int main ( int c, char** v ){

    QApplication app( c, v );
    QDialog d( NULL );

    QLayout * l = new QVBoxLayout();
    d.setLayout( l );

    addField("Name", l );
    addField("Lastname", l );
    addField("Birth year", l );
    addField("e-mail", l );

	l = new QHBoxLayout();
	l->addWidget( new QPushButton( "Submit", &d ) );
	l->addWidget( new QPushButton( "Cancel", &d ) );
	d.layout()->addItem(l);

	d.setWindowTitle( "Who are you?" );

    d.show();
    return app.exec();

}


void addField( char* fieldName, QLayout * parentLayout ){

	QWidget * parent = parentLayout->parentWidget();
	QLayout * l = new QHBoxLayout();

	l->setSpacing(10);

	l->addWidget( new QLabel( fieldName, parent ));
	l->addWidget( new QLineEdit( parent ) );

	parentLayout->addItem(l);

}

