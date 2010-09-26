#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>


int main (int argc, char **argv){
    QApplication app(argc,argv);
    QDialog d(NULL);

    QHBoxLayout *genderLay = new QHBoxLayout();
    genderLay->addWidget(new QRadioButton ("Male",&d));
    genderLay->addWidget(new QRadioButton ("Female",&d));

    QVBoxLayout *nameAndGender = new QVBoxLayout();
    nameAndGender->addWidget(new QLabel("Name:",&d));
    nameAndGender->addWidget(new QLineEdit(&d));
    nameAndGender->addWidget(new QLabel("Gender:",&d));
    nameAndGender->addLayout(genderLay);

    QVBoxLayout *labelsLay = new QVBoxLayout();
    labelsLay->addWidget(new QLabel("Adress:",&d));
    labelsLay->addWidget(new QLabel("Telephone:",&d));
    labelsLay->addWidget(new QLabel("Mobile:",&d));
    labelsLay->addWidget(new QLabel("www:",&d));

    QVBoxLayout *lineEditLay = new QVBoxLayout();
    lineEditLay->addWidget(new QLineEdit(&d));
    lineEditLay->addWidget(new QLineEdit(&d));
    lineEditLay->addWidget(new QLineEdit(&d));
    lineEditLay->addWidget(new QLineEdit(&d));

    QHBoxLayout *bottomLay = new QHBoxLayout();
    bottomLay->addLayout(nameAndGender);
    bottomLay->addSpacing(30);
    bottomLay->addLayout(labelsLay);
    bottomLay->addLayout(lineEditLay);

    QHBoxLayout *topLay = new QHBoxLayout();
    topLay->addWidget(new QLabel("Company name:",&d));
    topLay->addWidget(new QLineEdit(&d));

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(topLay);
    mainLayout->addLayout(bottomLay);

    QPushButton *exit = new QPushButton("Exit",&d);
    QObject::connect(exit,SIGNAL(clicked()),qApp,SLOT(quit()));
    mainLayout->addWidget(exit);

    d.setLayout(mainLayout);
    d.show();
    return app.exec();
}
