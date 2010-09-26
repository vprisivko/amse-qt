#include<stdio.h>
#include <QtGui/QApplication>
#include<QDialog>
#include<QPushButton>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QGridLayout>
#include<QRadioButton>
#include<QTextEdit>
#include<QLineEdit>
#include<QCheckBox>
#include<QComboBox>
#include<QLabel>

int main(int argc, char *argv[]) {
QApplication app(argc, argv);
QDialog d(NULL);
d.setWindowTitle("Information card");
d.setLayout(new QVBoxLayout());

QHBoxLayout *nameLayout = new QHBoxLayout();
QLineEdit *nameLine = new QLineEdit(&d);
QLabel *nameLabel = new QLabel("First Name ",&d);
nameLayout->addWidget(nameLabel);
nameLayout->addWidget(nameLine);
d.layout()->addItem(nameLayout);

QHBoxLayout *lastNameLayout = new QHBoxLayout();
QLineEdit *lNameLine = new QLineEdit(&d);
QLabel *lNameLabel = new QLabel("Last Name ",&d);
lastNameLayout->addWidget(lNameLabel);
lastNameLayout->addWidget(lNameLine);
d.layout()->addItem(lastNameLayout);

QHBoxLayout *radioLayout = new QHBoxLayout();
QRadioButton *maleSex = new QRadioButton("male",&d);
QRadioButton *femaleSex = new QRadioButton("female",&d);
QLabel *sexLabel = new QLabel("sex: ",&d);
radioLayout->addWidget(sexLabel);
radioLayout->addWidget(maleSex);
radioLayout->addWidget(femaleSex);
d.layout()->addItem(radioLayout);

QHBoxLayout *birthdayLayout = new QHBoxLayout();
QLabel *birthLabel = new QLabel("Birthday: ",&d);
QLineEdit *day = new QLineEdit("day",&d);
QComboBox *month = new QComboBox(&d);
month->addItem("January");
month->addItem("February");
month->addItem("March");
month->addItem("April");
month->addItem("Mai");
month->addItem("other...");
QLineEdit *year = new QLineEdit("year",&d);
QCheckBox *hide = new QCheckBox(QString("do not show my birthday"),&d);
birthdayLayout->addWidget(birthLabel);
birthdayLayout->addWidget(day);
birthdayLayout->addWidget(month);
birthdayLayout->addWidget(year);
birthdayLayout->addWidget(year);
birthdayLayout->addWidget(hide);
d.layout()->addItem(birthdayLayout);

QHBoxLayout *aboutLay = new QHBoxLayout();
aboutLay->addWidget(new QLabel("About Me: ",&d));
aboutLay->addWidget( new QTextEdit(&d));
d.layout()->addItem(aboutLay);

QVBoxLayout *contactLay = new QVBoxLayout();
QHBoxLayout *email = new QHBoxLayout();
email->addWidget( new QLabel("E-mail: ",&d));
email->addWidget( new QLineEdit(&d));
email->addWidget( new QLabel("example: newton@gmail.com ",&d));
QHBoxLayout *mobile = new QHBoxLayout();
mobile->addWidget( new QLabel("Mobile: ",&d));
mobile->addWidget( new QLineEdit(&d));
contactLay->addItem(email);
contactLay->addItem(mobile);
d.layout()->addItem(contactLay);

QHBoxLayout *buttonLay = new QHBoxLayout();
buttonLay->addWidget(new QPushButton("SAVE",&d));
buttonLay->addWidget(new QPushButton("CANCEL",&d));
d.layout()->addItem(buttonLay);

d.show();
return app.exec();
}

