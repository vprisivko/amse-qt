#include <QtGui/QApplication>
#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>

int main(int argc, char ** argv) {

        QApplication app(argc, argv);
        QDialog contactDialog( NULL );
        contactDialog.setWindowTitle("Contact information");
        contactDialog.setLayout( new QVBoxLayout() );

        QHBoxLayout * firstNameLayout = new QHBoxLayout();
        QLabel * firstNameLabel = new QLabel("First name: ", &contactDialog);
        QLineEdit * firstNameLine = new QLineEdit( &contactDialog );
        firstNameLayout->addWidget( firstNameLabel );
        firstNameLayout->addWidget( firstNameLine );
        contactDialog.layout()->addItem(firstNameLayout);

        QHBoxLayout * lastNameLayout = new QHBoxLayout();
        QLabel * lastNameLabel = new QLabel("Last name: ", &contactDialog);
        QLineEdit * lastNameLine = new QLineEdit( &contactDialog );
        lastNameLayout->addWidget( lastNameLabel );
        lastNameLayout->addWidget( lastNameLine );
        contactDialog.layout()->addItem(lastNameLayout);

        QHBoxLayout * birthdayLayout = new QHBoxLayout();
        QLabel * birthdayLabel = new QLabel("Date of birth: ", &contactDialog);

        QComboBox * day = new QComboBox( &contactDialog );      
        day->addItem("1");
        day->addItem("2");
        day->addItem("3");
        day->addItem("4");
        day->addItem("5");
        day->addItem("6");
        day->addItem("7");
        day->addItem("8");
        day->addItem("9");
        day->addItem("10");
        day->addItem("11");
        day->addItem("12");
        day->addItem("13");
        day->addItem("14");
        day->addItem("15");
        day->addItem("16");
        day->addItem("17");
        day->addItem("18");
        day->addItem("19");
        day->addItem("20");
        day->addItem("21");
        day->addItem("22");
        day->addItem("23");
        day->addItem("24");
        day->addItem("25");
        day->addItem("26");
        day->addItem("27");
        day->addItem("28");
        day->addItem("29");
        day->addItem("30");
        day->addItem("31");

        QComboBox * month = new QComboBox( &contactDialog );    
        month->addItem("January");
        month->addItem("February");
        month->addItem("March");
        month->addItem("April");
        month->addItem("May");
        month->addItem("June");
        month->addItem("July");
        month->addItem("August");
        month->addItem("September");
        month->addItem("November");
        month->addItem("December");

        QComboBox * year = new QComboBox( &contactDialog );     
        year->addItem("1970");
        year->addItem("1971");
        year->addItem("1972");
        year->addItem("1973");
        year->addItem("1974");
        year->addItem("1975");
        year->addItem("1976");
        year->addItem("1977");
        year->addItem("1978");
        year->addItem("1979");
        year->addItem("1980");
        year->addItem("1981");
        year->addItem("1982");
        year->addItem("1983");
        year->addItem("1984");
        year->addItem("1985");
        year->addItem("1986");
        year->addItem("1987");
        year->addItem("1988");
        year->addItem("1989");
        year->addItem("1990");
        year->addItem("1991");
        year->addItem("1992");
        year->addItem("1993");
        year->addItem("1994");
        year->addItem("1995");
        year->addItem("1996");
        year->addItem("1997");
        year->addItem("1998");
        year->addItem("1999");

        birthdayLayout->addWidget( birthdayLabel );
        birthdayLayout->addWidget( day );
        birthdayLayout->addWidget( month );
        birthdayLayout->addWidget( year );
        contactDialog.layout()->addItem( birthdayLayout );


        QHBoxLayout * buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget( new QPushButton ("Done", &contactDialog) );
        buttonLayout->addWidget( new QPushButton ("Cancel", &contactDialog) );
        contactDialog.layout()->addItem( buttonLayout );

        contactDialog.show();
        return app.exec();
}


