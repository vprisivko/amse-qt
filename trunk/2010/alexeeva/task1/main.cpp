#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QDialog d(NULL);

    d.setLayout(new QVBoxLayout);

	QFont font;
	font.setPointSize(15);
	font.setBold(true);

    QLabel * lab = new QLabel("Personal info", &d);
    lab->setAlignment(Qt::AlignCenter);
	lab->setFont(font);
    d.layout()->addWidget(lab);

    QHBoxLayout * layName = new QHBoxLayout();
    layName->addWidget(new QLabel("Name:	", &d));
    layName->addWidget(new QLineEdit("Jack", &d));
    d.layout()->addItem(layName);

    QHBoxLayout * laySName = new QHBoxLayout();
    laySName->addWidget(new QLabel("Surname:	", &d));
    laySName->addWidget(new QLineEdit("Smith", &d));
    d.layout()->addItem(laySName);

    QHBoxLayout * layEmail = new QHBoxLayout();
    layEmail->addWidget(new QLabel("Email:	", &d));
    layEmail->addWidget(new QLineEdit("jack.smith@aol.com", &d));
    d.layout()->addItem(layEmail);

    QHBoxLayout * layPhone = new QHBoxLayout();
    layPhone->addWidget(new QLabel("Phone:	", &d));
    layPhone->addWidget(new QLineEdit("001 415 570 0000", &d));
    d.layout()->addItem(layPhone);

    d.layout()->addWidget(new QLabel("Additional info:", &d));
    d.layout()->addWidget(new QTextEdit("I'm a qualified qt4 developer specializing in forms and dialogs.",&d));

    QHBoxLayout * lay2 = new QHBoxLayout();
    lay2->addWidget(new QPushButton("Submit", &d));
    lay2->addWidget(new QPushButton("Exit", &d));
    d.layout()->addItem(lay2);

    d.show();

    return app.exec();
}
