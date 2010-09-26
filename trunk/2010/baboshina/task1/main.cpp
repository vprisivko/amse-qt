#include <QtGui/QApplication>
#include <QVBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

int main(int c, char ** v)
{
    QApplication app(c, v);
    QDialog d(NULL);

    QVBoxLayout* layout = new QVBoxLayout;

    QHBoxLayout* surLayout = new QHBoxLayout;
    QLabel* surLabel = new QLabel;
    surLabel->setText("Surname");
    QLineEdit* surLineEdit = new QLineEdit;
    surLayout->addWidget(surLabel);
    surLayout->addWidget(surLineEdit);

    layout->insertLayout(-1, surLayout);

    QHBoxLayout* nameLayout = new QHBoxLayout;
    QLabel* nameLabel = new QLabel;
    nameLabel->setText("Name");
    QLineEdit* nameLineEdit = new QLineEdit;
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameLineEdit);

    layout->insertLayout(-1, nameLayout);

    QHBoxLayout* emailLayout = new QHBoxLayout;
    QLabel* emailLabel = new QLabel;
    emailLabel->setText("E-mail");
    QLineEdit* emailLineEdit = new QLineEdit;
    emailLayout->addWidget(emailLabel);
    emailLayout->addWidget(emailLineEdit);

    layout->insertLayout(-1, emailLayout);

    QHBoxLayout* phoneLayout = new QHBoxLayout;
    QLabel* phoneLabel = new QLabel;
    phoneLabel->setText("Phone");
    QLineEdit* phoneLineEdit = new QLineEdit;
    phoneLayout->addWidget(phoneLabel);
    phoneLayout->addWidget(phoneLineEdit);

    layout->insertLayout(-1, phoneLayout);

    QPushButton* okButton = new QPushButton ("OK", &d);

    d.setLayout(layout);
    d.layout()->addWidget(okButton);

    QObject::connect(okButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    d.show();

    return app.exec();
}




