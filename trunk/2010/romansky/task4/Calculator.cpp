#include "Calculator.h"

Calculator::Calculator(QWidget* p):QMainWindow(p){
 
  mycalc = new QDialog();
  mycurrentresult = 0;
  mylogname = new QLabel("Unsaved File");
  mylabelresult = new QLabel();
  myoperand = 0;
  mylogstringcount = 0;
  mylogresult = 0;
  mylog = NULL;
  mymessage = new QMessageBox();
  
  myinputline = new QLineEdit(QString::number(mycurrentresult),mycalc);
  mycalculationdialog = new QDialog();
 
  
  

  QHBoxLayout* buttonslayout = new QHBoxLayout();

  resize(640,480);

  

  QAction* open = new QAction("Open",this);
  QAction* save = new QAction("Save",this);
  QAction* calculate = new QAction("Calculate",this);
  QAction* revert = new QAction("Revert",this);



  menuBar()->addAction(open);
  menuBar()->addAction(save);
  menuBar()->addAction(revert);
  menuBar()->addAction(calculate);

  setCentralWidget(mycalculationdialog);
  mycalculationdialog->setLayout(new QVBoxLayout());
  mycalculationdialog->layout()->setAlignment(Qt::AlignTop);

  mylabelresult->setText(QString::number(mycurrentresult));
  statusBar()->addWidget(mylogname);
  statusBar()->addPermanentWidget(mylabelresult);
 
  QPushButton* add = new QPushButton("+",mycalc);
  QPushButton* sub = new QPushButton("-",mycalc);
  QPushButton* mul = new QPushButton("*",mycalc);
  QPushButton* div = new QPushButton("/",mycalc);  

  mycalc->setLayout(new QVBoxLayout);
  mycalc->layout()->addWidget(myinputline);
  mycalc->layout()->addItem(buttonslayout);
  buttonslayout->addWidget(add);
  buttonslayout->addWidget(sub);
  buttonslayout->addWidget(mul);
  buttonslayout->addWidget(div);

  mycalculationdialog->setLayout(new QHBoxLayout());
  
  QObject::connect(add, SIGNAL(clicked()), this, SLOT(Add()));
  QObject::connect(sub, SIGNAL(clicked()), this, SLOT(Sub()));
  QObject::connect(mul, SIGNAL(clicked()), this, SLOT(Mul()));
  QObject::connect(div, SIGNAL(clicked()), this, SLOT(Div()));
  
  QObject::connect(calculate, SIGNAL(triggered()), this, SLOT(Calc()));
  QObject::connect(open, SIGNAL(triggered()), this, SLOT(Open()));
  QObject::connect(save, SIGNAL(triggered()), this, SLOT(Save()));
  QObject::connect(revert, SIGNAL(triggered()), this, SLOT(Revert()));
}

void Calculator::Add(){
  QLabel* newoperation = new QLabel();
  myoperand = myinputline->text().toDouble();
  newoperation->setText(QString::number(mycurrentresult)+"+"+QString::number(myoperand)+"="+QString::number(mycurrentresult+myoperand));
  myoperations.append(newoperation);
  mycurrentresult = mycurrentresult + myoperand; 
  mycalculationdialog->layout()->addWidget(newoperation);
  mylabelresult->setText(QString::number(mycurrentresult));
  myinputline->setText(QString::number(mycurrentresult));
}

void Calculator::Sub(){
  QLabel* newoperation = new QLabel();
  myoperand = myinputline->text().toDouble();
  newoperation->setText(QString::number(mycurrentresult)+"-"+QString::number(myoperand)+"="+QString::number(mycurrentresult-myoperand));
  myoperations.append(newoperation);
  mycurrentresult = mycurrentresult - myoperand; 
  mycalculationdialog->layout()->addWidget(newoperation);
  mylabelresult->setText(QString::number(mycurrentresult));
  myinputline->setText(QString::number(mycurrentresult));
}

void Calculator::Mul(){
  QLabel* newoperation = new QLabel();
  myoperand = myinputline->text().toDouble();
  newoperation->setText(QString::number(mycurrentresult)+"*"+QString::number(myoperand)+"="+QString::number(mycurrentresult*myoperand));
  myoperations.append(newoperation);
  mycurrentresult = mycurrentresult * myoperand; 
  mycalculationdialog->layout()->addWidget(newoperation);
  mylabelresult->setText(QString::number(mycurrentresult));
  myinputline->setText(QString::number(mycurrentresult));
}

void Calculator::Div(){
  QLabel* newoperation = new QLabel();
  myoperand = myinputline->text().toDouble();
  if (myoperand == 0){
    mymessage->setText("division on 0");
    mymessage->show();
  } else {
    myoperand = myinputline->text().toDouble();
    newoperation->setText(QString::number(mycurrentresult)+"/"+QString::number(myoperand)+"="+QString::number(mycurrentresult/myoperand));
    myoperations.append(newoperation);
    mycurrentresult = mycurrentresult / myoperand; 
    mycalculationdialog->layout()->addWidget(newoperation);
    mylabelresult->setText(QString::number(mycurrentresult));
    myinputline->setText(QString::number(mycurrentresult));
  }
}

void Calculator::Calc(){
  if (mycalc->isVisible()) {
    mycalc->hide();
  } else {
    mycalc->show();
  }
}

void Calculator::Open(){
  QString filename;
  QFile* file;
  bool f;
  bool readresult=false;
  const char* filetostring;
  QLabel* newoperation;
  QString currentstring;
  int i;
  filename = QFileDialog::getOpenFileName(this);
  file = new QFile(filename);
  if (filename == ""){
    return;
  } else {
    f = file->open(QIODevice::ReadWrite | QIODevice::Text);
    if (f) {
      mylog = file;
      for (i = myoperations.size()-1;i>=0;--i){
        delete myoperations.value(i);
      }
      myoperations.clear();   
      filetostring = (const char*) file->map(0,file->size());  
      i=0;
      mylogstringcount=0;
      while(i < file->size()){

        currentstring = "";
        while(filetostring[i] != '\n'){
          currentstring = currentstring + filetostring[i];
          i=i+1;
        }
        i=i+1;
        if (!readresult){
          mycurrentresult = currentstring.toDouble();
          mylogresult = mycurrentresult;
          mylabelresult->setText(QString::number(mycurrentresult));
          readresult = true;
        } else {
          newoperation = new QLabel(currentstring);
          myoperations.append(newoperation);
          mycalculationdialog->layout()->addWidget(newoperation);
          mylogstringcount++;      
        }
      }
      mylogname->setText(filename);
      myinputline->setText(QString::number(mycurrentresult));
      file->close();
    } else {
      return;
    }
  }
  
}

void Calculator::Save(){
  QString filename;
  QFile* file;
  bool f;
  int i;
  filename = QFileDialog::getSaveFileName(this);
  file = new QFile(filename);
  mylogstringcount = myoperations.size();
  mylogresult = mycurrentresult;
  f = file->open(QIODevice::WriteOnly | QIODevice::Text);
  if (f){
    mylog = file;
    mylogname->setText(filename);
    file->write(QByteArray((mylabelresult->text() + "\n").toAscii()));
    for (i=0;i<myoperations.size();++i){
      file->write(QByteArray(myoperations.value(i)->text().toAscii()));
      file->write("\n");
    }
    file->close();
  }
}

void Calculator::Revert(){
  int i;
  QVector<QLabel*>::iterator j;
  if (mylog==NULL){
    for (i = myoperations.size()-1;i>=0;--i){
      delete myoperations.value(i);
    }
    myoperations.clear();
  } else {
    j=myoperations.begin();
    for (i = myoperations.size()-1;i>=mylogstringcount;--i){
      delete myoperations.value(i);
    }  
    for (i = 0;i<mylogstringcount;++i){
      ++j;
    }  
    myoperations.erase(j,myoperations.end());  
  } 
  mycurrentresult = mylogresult;
  mylabelresult->setText(QString::number(mycurrentresult));
  myinputline->setText(QString::number(mycurrentresult));
}

