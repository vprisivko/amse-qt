#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
int main(int c,char** v){
  QApplication app(c,v);
  QDialog d(NULL);

  QVBoxLayout* lmain = new QVBoxLayout(&d);
  QHBoxLayout* lname = new QHBoxLayout();
  QHBoxLayout* lsurname = new QHBoxLayout();
  QHBoxLayout* lphone = new QHBoxLayout();
  QHBoxLayout* lbutton = new QHBoxLayout();

  QLabel* labelname = new QLabel();
  QLabel* labelsurname = new QLabel();
  QLabel* labelphone = new QLabel();  
  QPushButton* p =new QPushButton("Ok");

  QObject::connect(p,SIGNAL(clicked()),qApp,SLOT(quit()));

  d.setLayout(lmain);
  lmain->addLayout(lname);
  lmain->addLayout(lsurname);
  lmain->addLayout(lphone);
  lmain->addLayout(lbutton);
  


  lname->addWidget(labelname);
  labelname->setText("Name              ");
  lname->addWidget(new QLineEdit());

  lsurname->addWidget(labelsurname);
  labelsurname->setText("Surname         ");
  lsurname->addWidget(new QLineEdit());

  lphone->addWidget(labelphone);
  labelphone->setText("Phone number");
  lphone->addWidget(new QLineEdit());

  lbutton->addWidget(p);  

  d.show();
  return app.exec();
}
