#include <QDialog>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QCheckBox>

int main(int c, char **v) {
	QApplication app(c, v);
	QDialog d(NULL);
	d.setLayout(new QVBoxLayout());

	QHBoxLayout *nameLayout = new QHBoxLayout();
	nameLayout -> addWidget(new QLabel("Enter your name: ", &d));
	nameLayout -> addWidget(new QLineEdit(&d));
	d.layout() -> addItem(nameLayout);

	QHBoxLayout *surnameLayout = new QHBoxLayout();
	surnameLayout -> addWidget(new QLabel("Enter your surname: ", &d));
	surnameLayout -> addWidget(new QLineEdit(&d));
	d.layout() -> addItem(surnameLayout);


	QHBoxLayout *genderLayout = new QHBoxLayout();
	genderLayout -> addWidget(new QLabel("Select your gender: ", &d));
	genderLayout -> addWidget(new QRadioButton("Female", &d));
	genderLayout -> addWidget(new QRadioButton("Male", &d));
	d.layout() -> addItem(genderLayout);

	QVBoxLayout *animalLayout = new QVBoxLayout();
	animalLayout -> addWidget(new QLabel("Whats animals did you love?", &d));
	animalLayout -> addWidget(new QCheckBox("Elepfant", &d));
	animalLayout -> addWidget(new QCheckBox("Cat", &d));
	animalLayout -> addWidget(new QCheckBox("Dog", &d));
	animalLayout -> addWidget(new QCheckBox("Tiger", &d));
	animalLayout -> addWidget(new QCheckBox("Frog", &d));
		QHBoxLayout *otherLayout = new QHBoxLayout();
		otherLayout -> addWidget(new QCheckBox("Other", &d));
		otherLayout -> addWidget(new QLineEdit(&d));
		animalLayout -> addItem(otherLayout);
	d.layout() -> addItem(animalLayout);

	QHBoxLayout *buttonsLayout = new QHBoxLayout();
	buttonsLayout -> addWidget(new QPushButton("Save", &d));
	buttonsLayout -> addWidget(new QPushButton("Exit", &d));
	d.layout() -> addItem(buttonsLayout);

	d.show();
	return app.exec();
}
