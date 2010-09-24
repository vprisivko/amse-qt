#include <QApplication>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QTextEdit>

int main(int c, char **v) {
	QApplication app(c, v);
	QDialog d(NULL);

	QVBoxLayout *lay1 = new QVBoxLayout();
	lay1->addWidget(new QLabel("Last name", &d));
        lay1->addWidget(new QLabel("First name", &d));
	lay1->addWidget(new QLabel("Middle name", &d));

	QVBoxLayout *lay2 = new QVBoxLayout();
        lay2->addWidget(new QLineEdit("123", &d));
        lay2->addWidget(new QLineEdit(&d));
        lay2->addWidget(new QLineEdit(&d));

	QHBoxLayout *layFIO = new QHBoxLayout();
	layFIO->addItem(lay1);
        layFIO->addItem(lay2);

	QHBoxLayout *laySex = new QHBoxLayout();
        laySex->addWidget(new QRadioButton(&d));
        laySex->addWidget(new QLabel("Male", &d));
        laySex->addWidget(new QRadioButton(&d));
        laySex->addWidget(new QLabel("Female", &d));

	QHBoxLayout *layButton = new QHBoxLayout();
	layButton->addWidget(new QPushButton("OK", &d));
	layButton->addWidget(new QPushButton("Cancel", &d));
	layButton->addWidget(new QPushButton("Apply", &d));
	
        QLabel *info1 = new QLabel("Phone", &d);
        QLabel *info2 = new QLabel("e-mail", &d);
        QLabel *info3 = new QLabel("Address", &d);
        QLabel *info4 = new QLabel("Comment", &d);
        QLineEdit *info5 = new QLineEdit(&d);
        QLineEdit *info6 = new QLineEdit(&d);
        QTextEdit *info7 = new QTextEdit(&d);
        QTextEdit *info8 = new QTextEdit(&d);

        QGridLayout *layInfo = new QGridLayout();
        layInfo->addWidget(info1, 1, 0);
        layInfo->addWidget(info2, 2, 0);
        layInfo->addWidget(info3, 3, 0);
        layInfo->addWidget(info4, 4, 0);
        layInfo->addWidget(info5, 1, 1);
        layInfo->addWidget(info6, 2, 1);
        layInfo->addWidget(info7, 3, 1);
        layInfo->addWidget(info8, 4, 1);



	QVBoxLayout *lay = new QVBoxLayout();
	lay->addItem(layFIO);
	lay->addItem(laySex);
        lay->addItem(layInfo);
        lay->addItem(layButton);

	d.setLayout(lay);
	d.show();
	return app.exec();
}
