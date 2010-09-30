#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QRadioButton>

int main(int c, char** v) {
    QApplication app(c,v);
    QDialog d(NULL);
    d.setLayout(new QVBoxLayout);
    QHBoxLayout *l = new QHBoxLayout();
    l->addWidget(new QLabel("You can write", &d));
    l->addWidget(new QLineEdit("some text", &d));
    l->addWidget(new QLabel("<-here", &d));
    d.layout()->addItem(l);
    d.layout()->addWidget(new QPushButton("Press me again!", &d));
    d.layout()->addWidget(new QCheckBox("Surprise, CHECKBOX!!!", &d));
    QGridLayout *l1 = new QGridLayout();
    l1->addWidget(new QRadioButton("Radio...", &d),0,0);
    l1->addWidget(new QRadioButton("...button!", &d),0,1);
    l1->addWidget(new QRadioButton("...", &d),1,0);
    l1->addWidget(new QRadioButton("...", &d),2,1);
    l1->addWidget(new QRadioButton("...", &d),3,2);
    l1->addWidget(new QRadioButton("...", &d),4,3);
    l1->addWidget(new QRadioButton("...", &d),5,4);
    l1->addWidget(new QRadioButton("...", &d),6,5);
    l1->addWidget(new QRadioButton("...", &d),6,0);
    l1->addWidget(new QRadioButton("...", &d),5,1);
    l1->addWidget(new QRadioButton("...", &d),4,2);
    l1->addWidget(new QRadioButton("...", &d),3,3);
    l1->addWidget(new QRadioButton("...", &d),2,4);
    l1->addWidget(new QRadioButton("...", &d),1,5);
    l1->addWidget(new QLabel("lots of them!", &d),6,3);
    d.layout()->addItem(l1);
    QHBoxLayout *l2 = new QHBoxLayout();
    l2->addWidget(new QPushButton("OK", &d),Qt::AlignRight);
    l2->addWidget(new QPushButton("Cancel", &d),Qt::AlignRight);
    l2->addWidget(new QPushButton("Don't know", &d),Qt::AlignRight);
    d.layout()->addItem(l2);
    d.show();
    return app.exec();
}
