#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>

int main( int argc, char* argv[] ){
    QApplication app( argc, argv );
    QDialog d( NULL );

    d.setWindowTitle( "Calling card" );
    d.setLayout( new QVBoxLayout() );

    QVBoxLayout* fullNameLayout = new QVBoxLayout();
    QHBoxLayout* nameLayout = new QHBoxLayout();
    nameLayout->addWidget( new QLabel( "Name : ", &d ) );
    nameLayout->addWidget( new QLineEdit( &d ) );
    QHBoxLayout* surnameLayout = new QHBoxLayout();
    surnameLayout->addWidget( new QLabel( "Surname : ", &d ) );
    surnameLayout->addWidget( new QLineEdit( &d ) );
    fullNameLayout->addItem( nameLayout );
    fullNameLayout->addItem( surnameLayout );
    d.layout()->addItem( fullNameLayout );

    QVBoxLayout* genderLayout = new QVBoxLayout();
    genderLayout->addWidget( new QLabel( "Gender : ", &d ) );
    QHBoxLayout* rbtLayout = new QHBoxLayout();
    rbtLayout->addWidget( new QRadioButton( "Male", &d ) );
    rbtLayout->addWidget( new QRadioButton( "Female", &d ) );
    genderLayout->addItem( rbtLayout );
    d.layout()->addItem( genderLayout );

    QHBoxLayout* phoneLayout = new QHBoxLayout();
    phoneLayout->addWidget( new QLabel( "Phone number : ", &d ) );
    phoneLayout->addWidget( new QLineEdit( &d ) );
    d.layout()->addItem( phoneLayout );

    QHBoxLayout* mailLayout = new QHBoxLayout();
    mailLayout->addWidget( new QLabel( "E-mail : ", &d ) );
    mailLayout->addWidget( new QLineEdit( &d ) );
    d.layout()->addItem( mailLayout );


    QPushButton* saveButton = new QPushButton( "Save", &d );
    QPushButton* quitButton = new QPushButton( "Quit", &d );

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget( saveButton );
    buttonLayout->addWidget( quitButton );
    d.layout()->addItem( buttonLayout );

    QObject::connect( saveButton, SIGNAL( clicked() ), qApp, SLOT( quit() ) );
    QObject::connect( quitButton, SIGNAL( clicked() ), qApp, SLOT( quit() ) );

    d.show();
    return app.exec();

}
