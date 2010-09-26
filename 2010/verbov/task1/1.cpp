#include <QApplication>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QRadioButton>
#include <QPushButton>

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	QDialog dialog(NULL);
	dialog.setLayout(new QVBoxLayout());

	dialog.layout()->addWidget(new QLabel("Enter your personal information:", &dialog));

	QHBoxLayout *topLayout = new QHBoxLayout();
	topLayout->setSpacing(2);
	
	QVBoxLayout *nameLayout = new QVBoxLayout();
	nameLayout->addWidget(new QLabel("Fist name: ", &dialog));
	nameLayout->addWidget(new QLineEdit(&dialog));
	nameLayout->addWidget(new QLabel("Second name: ", &dialog));
	nameLayout->addWidget(new QLineEdit(&dialog));
	topLayout->addItem(nameLayout);

	QVBoxLayout *contactsLayout = new QVBoxLayout();
	contactsLayout->addWidget(new QLabel("E-mail: ", &dialog));
	contactsLayout->addWidget(new QLineEdit(&dialog));
	contactsLayout->addWidget(new QLabel("Phone number: ", &dialog));
	contactsLayout->addWidget(new QLineEdit(&dialog));
	topLayout->addItem(contactsLayout);

	dialog.layout()->addItem(topLayout);

	QHBoxLayout *genderLayout = new QHBoxLayout();
	genderLayout->addWidget(new QLabel("Gender:", &dialog));
	genderLayout->addWidget(new QRadioButton("Male", &dialog));
	genderLayout->addWidget(new QRadioButton("Female", &dialog));
	dialog.layout()->addItem(genderLayout);
	
	QVBoxLayout *commentLayout = new QVBoxLayout();
	commentLayout->addWidget(new QLabel("Additional comment: ", &dialog));
	commentLayout->addWidget(new QTextEdit(&dialog));
	dialog.layout()->addItem(commentLayout);

	QHBoxLayout *buttonsLayout = new QHBoxLayout();
	buttonsLayout->addWidget(new QPushButton("Ok", &dialog));
	buttonsLayout->addWidget(new QPushButton("Cancel", &dialog));
	dialog.layout()->addItem(buttonsLayout);

	dialog.show();
	return app.exec();
}
