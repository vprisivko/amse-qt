#include "MyCalc.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
myCalc::myCalc(QWidget* parent): QDialog( parent ){
  temp1 = 0;
  temp2 = 0;
  znak = -1;
  setLayout(new QVBoxLayout());
  l = new QLineEdit(QString::number(0), this);
  l->setAlignment(Qt::AlignRight);
  layout()->addWidget(l);
  QHBoxLayout *hl = new QHBoxLayout();
  a = new QPushButton("+", this);
  s = new QPushButton("-", this);
  m = new QPushButton("*", this);
  d = new QPushButton("/", this);
  hl->addWidget(a);
  hl->addWidget(s);
  hl->addWidget(m);
  hl->addWidget(d);
  layout()->addItem(hl);
  connect(a, SIGNAL(clicked()), this, SLOT(Add()) );
  connect(s, SIGNAL(clicked()), this, SLOT(Sub()) );
  connect(m, SIGNAL(clicked()), this, SLOT(Mul()) );
  connect(d, SIGNAL(clicked()), this, SLOT(Div()) );
}
void myCalc::What(){
  if (znak == -2){
    l->setText(QString::number(temp1)); 
  }
  if ( znak == -1){
    temp1 = temp2;
  }
  else if (znak == 0){//"+"
    emit signalAdd();
    temp1 += temp2;
  }
  else if (znak == 1){//"-"
    emit signalSub();
    temp1 -=temp2;
  }
  else if (znak == 2){//"*"
    emit signalMul();
    temp1 *=temp2;
  }
  else if (znak == 3){//"/"
    emit signalDiv();
    temp1 /=temp2;
  }
}

void myCalc::Add(){
  double temp =  l->text().toDouble();
  temp2 = temp;
  What(); 
  znak = 0;  
  l->setText(QString::number(temp1)); 
}



void myCalc::Sub(){
  double temp =  l->text().toDouble();
  temp2 = temp;
  What(); 
  znak = 1;  
  l->setText(QString::number(temp1)); 
}


void myCalc::Mul(){
  double temp =  l->text().toDouble();
  temp2 = temp;
  What(); 
  znak = 2;  
  l->setText(QString::number(temp1)); 
}


void myCalc::Div(){
  double temp =  l->text().toDouble();
  temp2 = temp;
  What(); 
  znak = 3;  
  l->setText(QString::number(temp1)); 
}


