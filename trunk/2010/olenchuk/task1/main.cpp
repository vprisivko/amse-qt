#include <QtGui>

int main(int argc, char *argv[]) {
    	QApplication app(argc, argv);
	QDialog cv(NULL);

	cv.setLayout(new QVBoxLayout);

	QFont font;
	font.setPointSize(13);
	font.setBold(true);

	QLabel *title = new QLabel("Personal info");
	title->setAlignment(Qt::AlignCenter);
	title->setFont(font);
	cv.layout()->addWidget(title);

	QHBoxLayout *surnameLayout = new QHBoxLayout();
	surnameLayout->addWidget(new QLabel("Surname:", &cv));
	surnameLayout->addWidget(new QLineEdit(&cv));
	cv.layout()->addItem(surnameLayout);

	QHBoxLayout *nameLayout = new QHBoxLayout();
	nameLayout->addWidget(new QLabel("Name:", &cv));
	nameLayout->addWidget(new QLineEdit(&cv));
	cv.layout()->addItem(nameLayout);

	QHBoxLayout *emailLayout = new QHBoxLayout();
	emailLayout->addWidget(new QLabel("Email:", &cv));
	emailLayout->addWidget(new QLineEdit(&cv));
	cv.layout()->addItem(emailLayout);

	cv.layout()->addWidget(new QLabel("Tell us about yourself:", &cv));
	cv.layout()->addWidget(new QTextEdit(&cv));

	QHBoxLayout *buttonLayout = new QHBoxLayout();
	buttonLayout->addWidget(new QPushButton("Send", &cv));
	buttonLayout->addWidget(new QPushButton("Exit", &cv));
	cv.layout()->addItem(buttonLayout);

	cv.show();

	return app.exec();
}


