#include <QDialog>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QComboBox>
#include <QCheckBox>

int main(int c, char **v) {
	QApplication app(c,v);
	QDialog d(NULL);
	d.setWindowTitle("First QT app");
	d.setLayout(new QVBoxLayout());

	QHBoxLayout *maleLayout = new QHBoxLayout();
	maleLayout->addWidget(new QLabel("Your gender: ", &d));
	QVBoxLayout *radioLayout = new QVBoxLayout();
	radioLayout->addWidget(new QRadioButton("Male", &d));
	radioLayout->addWidget(new QRadioButton("Female", &d));
	maleLayout->addItem(radioLayout);
	d.layout()->addItem(maleLayout);

	QHBoxLayout *cellLayout = new QHBoxLayout();
	cellLayout->addWidget(new QLabel("Your cell: ", &d));
	cellLayout->addWidget(new QLineEdit(&d));
	d.layout()->addItem(cellLayout);

	QHBoxLayout *countryLayout = new QHBoxLayout();
	countryLayout->addWidget(new QLabel("Your country: ", &d));
	QComboBox *countryList = new QComboBox(&d);
	countryList->addItem("Olbania");
	countryList->addItem("Babruissk");
	countryList->addItem("Russian Federation");
	countryList->addItem("United Kingdom");
	countryList->addItem("USA");
	countryList->addItem("don't know");
	countryLayout->addWidget(countryList);
	d.layout()->addItem(countryLayout);

	QHBoxLayout *agreeLayout = new QHBoxLayout();
	agreeLayout->addWidget(new QCheckBox("I agree to tell this information to FBI", &d));
	d.layout()->addItem(agreeLayout);

	QPushButton *button = new QPushButton("Send", &d);
	d.layout()->addWidget(button);

	QObject::connect(button, SIGNAL(clicked()), qApp, SLOT(quit()));
	d.show();
	return app.exec();
}
