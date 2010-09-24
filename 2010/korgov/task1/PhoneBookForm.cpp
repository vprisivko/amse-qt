#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	QDialog mainDialog;

	QVBoxLayout *mainLayout =  new QVBoxLayout (&mainDialog);
	QHBoxLayout *hBoxLayout = new QHBoxLayout();
	QVBoxLayout *labelsVBoxLayout = new QVBoxLayout();
	QVBoxLayout *lineEditsVBoxLayout = new QVBoxLayout();
	QHBoxLayout *buttonsHBoxLayout = new QHBoxLayout();

	int spacing = 5;
	mainLayout->setSpacing(spacing);
	hBoxLayout->setSpacing(spacing);
	labelsVBoxLayout->setSpacing(spacing);
	lineEditsVBoxLayout->setSpacing(spacing);
	buttonsHBoxLayout->setSpacing(spacing);

	labelsVBoxLayout->addWidget(new QLabel("First Name:",&mainDialog));
	labelsVBoxLayout->addWidget(new QLabel("Last Name:",&mainDialog));
	labelsVBoxLayout->addWidget(new QLabel("Phone:",&mainDialog));
	labelsVBoxLayout->addWidget(new QLabel("Address:",&mainDialog));

	lineEditsVBoxLayout->addWidget(new QLineEdit(&mainDialog));
	lineEditsVBoxLayout->addWidget(new QLineEdit(&mainDialog));
	lineEditsVBoxLayout->addWidget(new QLineEdit(&mainDialog));
	lineEditsVBoxLayout->addWidget(new QLineEdit(&mainDialog));

	buttonsHBoxLayout->addStretch();
	buttonsHBoxLayout->addWidget(new QPushButton ("Save",&mainDialog));
	QPushButton *exitButton = new QPushButton ("Exit",&mainDialog);
	buttonsHBoxLayout->addWidget(exitButton);

	hBoxLayout->addLayout(labelsVBoxLayout);
	hBoxLayout->addLayout(lineEditsVBoxLayout);

	mainLayout->addLayout(hBoxLayout);
	mainLayout->addWidget(new QLabel("Additional information:",&mainDialog));
	mainLayout->addWidget(new QTextEdit(&mainDialog));
	mainLayout->addLayout(buttonsHBoxLayout);

	mainDialog.setLayout(mainLayout);

	QObject::connect(exitButton,SIGNAL(clicked()),&app,SLOT(quit()));

    mainDialog.show ();
    return app.exec();
}
