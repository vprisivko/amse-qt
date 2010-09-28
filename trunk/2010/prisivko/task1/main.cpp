#include <QtGui/QApplication>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QRadioButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>

int main(int argc, char *argv[]) 
{
	QApplication app(argc, argv);
	
	QDialog d(0);
	
	d.setWindowTitle("Task 1");
	d.setLayout(new QVBoxLayout());
	
	QHBoxLayout *firstNameLayout = new QHBoxLayout();
	
	QLabel *firstNameLabel = new QLabel("First Name ", &d);
	firstNameLayout->addWidget(firstNameLabel);
	
	QLineEdit *firstNameLineEdit = new QLineEdit(&d);
	firstNameLayout->addWidget(firstNameLineEdit);
	
	d.layout()->addItem(firstNameLayout);

	QHBoxLayout *lastNameLayout = new QHBoxLayout();
	
	QLabel *lastNameLabel = new QLabel("Last Name ",&d);
	lastNameLayout->addWidget(lastNameLabel);
	
	QLineEdit *lastNameLineEdit = new QLineEdit(&d);
	lastNameLayout->addWidget(lastNameLineEdit);
	
	d.layout()->addItem(lastNameLayout);

	QHBoxLayout *radioButtonLayout = new QHBoxLayout();
	
	QRadioButton *maleSexRadioButton = new QRadioButton("male",&d);
	QRadioButton *femaleSexRadioButton = new QRadioButton("female",&d);
	QLabel *sexLabel = new QLabel("Sex: ",&d);
	
	radioButtonLayout->addWidget(sexLabel);
	radioButtonLayout->addWidget(maleSexRadioButton);
	radioButtonLayout->addWidget(femaleSexRadioButton);
	
	d.layout()->addItem(radioButtonLayout);

	QHBoxLayout *birthdayLayout = new QHBoxLayout();
	
	QLabel *birthdayLabel = new QLabel("Birthday: ",&d);
	
	QLineEdit *dayLineEdit = new QLineEdit("day",&d);
	
	QComboBox *monthComboBox = new QComboBox(&d);
	
	monthComboBox->addItem("January");
	monthComboBox->addItem("February");
	monthComboBox->addItem("March");
	monthComboBox->addItem("April");
	monthComboBox->addItem("May");
	monthComboBox->addItem("June");
	monthComboBox->addItem("July");
	monthComboBox->addItem("August");
	monthComboBox->addItem("September");
	monthComboBox->addItem("October");
	monthComboBox->addItem("November");
	monthComboBox->addItem("December");
	
	QLineEdit *yearLineEdit = new QLineEdit("year", &d);
	
	birthdayLayout->addWidget(birthdayLabel);
	birthdayLayout->addWidget(dayLineEdit);
	birthdayLayout->addWidget(monthComboBox);
	birthdayLayout->addWidget(yearLineEdit);
	
	d.layout()->addItem(birthdayLayout);

	QHBoxLayout *buttonLayout = new QHBoxLayout();
	
	buttonLayout->addWidget(new QPushButton("Save", &d));
	buttonLayout->addWidget(new QPushButton("Cancel", &d));	

	d.layout()->addItem(buttonLayout);

	d.show();
	
	return app.exec();
}

