#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

int main ( int c, char** v){
    QApplication app(c,v);
    QDialog d(NULL);
    d.setLayout(new QVBoxLayout);
    
    QHBoxLayout* lay1 = new QHBoxLayout();
    lay1->addWidget(new QLabel("Name",&d));
    lay1->addWidget(new QLineEdit("",&d));
    
    QHBoxLayout* lay2 = new QHBoxLayout();
    lay2->addWidget(new QLabel("Surname",&d));
    lay2->addWidget(new QLineEdit("",&d));
    
    QHBoxLayout* lay3 = new QHBoxLayout();
    lay3->addWidget(new QLabel("Patronymic",&d));
    lay3->addWidget(new QLineEdit("",&d));
    
    QHBoxLayout* lay4 = new QHBoxLayout();
    lay4->addWidget(new QLabel("Number",&d));
    lay4->addWidget(new QLineEdit("",&d));
    
    d.layout()->addItem(lay1);
    d.layout()->addItem(lay2);
    d.layout()->addItem(lay3);
    d.layout()->addItem(lay4);
    d.layout()->addWidget(new QPushButton("Make",&d));
    d.show();
    return app.exec();
}
