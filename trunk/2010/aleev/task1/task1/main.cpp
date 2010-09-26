#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    QDialog d(NULL);

    d.setWindowTitle("Business card");
    d.setLayout(new QVBoxLayout());

    QVBoxLayout *nameLayout = new QVBoxLayout();
    nameLayout->addWidget(new QLabel("Name : ", &d));
    nameLayout->addWidget(new QLineEdit(&d));
    nameLayout->addWidget(new QLabel("Surname : ", &d));
    nameLayout->addWidget(new QLineEdit(&d));
    d.layout()->addItem(nameLayout);

    QVBoxLayout *genderLayout = new QVBoxLayout();
    genderLayout->addWidget(new QLabel("Gender : ", &d));
    QHBoxLayout *rbtLayout = new QHBoxLayout();
    rbtLayout->addWidget(new QRadioButton("Male", &d));
    rbtLayout->addWidget(new QRadioButton("Female", &d));
    genderLayout->addItem(rbtLayout);
    d.layout()->addItem(genderLayout);

    QHBoxLayout  *phoneLayout = new QHBoxLayout();
    phoneLayout->addWidget(new QLabel("Phone numbers : ", &d));
    phoneLayout->addWidget(new QLineEdit(&d));
    d.layout()->addItem(phoneLayout);

    QHBoxLayout  *mailLayout = new QHBoxLayout();
    mailLayout->addWidget(new QLabel("E-mail : ", &d));
    mailLayout->addWidget(new QLineEdit(&d));
    d.layout()->addItem(mailLayout);


    QPushButton *saveBt = new QPushButton("Save", &d);
    QPushButton *quitBt = new QPushButton("Quit", &d);

    QHBoxLayout *btLayout = new QHBoxLayout();
    btLayout->addWidget(saveBt);
    btLayout->addWidget(quitBt);
    d.layout()->addItem(btLayout);

    QObject::connect(saveBt, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(quitBt, SIGNAL(clicked()), qApp, SLOT(quit()));

    d.show();
    return app.exec();

}
