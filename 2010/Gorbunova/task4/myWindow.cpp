#include "myWindow.h"
#include <QMenuBar>
#include <QAction>
#include <QStatusBar>
#include <QSettings>
#include <QToolBar>
#include <QFileDialog>
#include <QTextEdit>
#include <QTextStream>
#include <QStringList>
myWindow::myWindow(QWidget* parent): QMainWindow( parent ){
  myName = "";
  nameLabel = new QLabel("File Name: "+myName,this);
  lastResult = 0;
  resultLabel = new QLabel("Last Result : "+QString::number(lastResult));
  makeAction(); 
 
  c = new myCalc(this);
  
  makeMenu();
  makeToolbar();
  makeCentralText();
  makeStatusBar();
  connection();
  
}
void myWindow::makeStatusBar(){
  statusBar()->addWidget(nameLabel,1);
  statusBar()->addWidget(resultLabel,1);
}
void myWindow::makeCentralText(){
  CentralText = new QTextEdit();
  CentralText->setReadOnly(true);
  setCentralWidget(CentralText);
}
void myWindow::makeToolbar(){
  QToolBar* toolbar=addToolBar("toolbar");
  toolbar->addAction(Open);
  toolbar->addAction(Save);
  toolbar->addAction(Revert);
}
  
void myWindow::makeMenu(){
  QMenu* menu = menuBar()->addMenu("Menu");
  menu->addAction(Open);
  menu->addAction(Save);
  menu->addAction(Revert);
  menu->addAction(calcul);
}

void myWindow::makeAction(){
  Open = new QAction("&Open", this);
  Save = new QAction("&Save", this);
  Revert = new QAction("&Revert", this);
  calcul = new QAction("&Calculator", this);
}
 
void myWindow::connection(){
  connect(calcul, SIGNAL(triggered()), this, SLOT(Calc()));
  connect(c, SIGNAL(signalAdd()),this, SLOT(Add()));
  connect(c, SIGNAL(signalSub()),this, SLOT(Sub()));
  connect(c, SIGNAL(signalMul()),this, SLOT(Mul()));
  connect(c, SIGNAL(signalDiv()),this, SLOT(Div()));
  connect(Open, SIGNAL(triggered()), this, SLOT(fileOpen()));
  connect(Save, SIGNAL(triggered()), this, SLOT(fileSave()));
  connect(Revert, SIGNAL(triggered()), this, SLOT(fileRevert()));
} 


void myWindow::Add(){
  lastResult = c->temp1+c->temp2;
  CentralText->append(QString::number(c->temp1)+"+"+QString::number(c->temp2)+"="+QString::number(lastResult));
}

void myWindow::Sub(){
  lastResult = c->temp1-c->temp2;
  CentralText->append(QString::number(c->temp1)+"-"+QString::number(c->temp2)+"="+QString::number(lastResult));
}

void myWindow::Mul(){
  lastResult = c->temp1*c->temp2;
  CentralText->append(QString::number(c->temp1)+"*"+QString::number(c->temp2)+"="+QString::number(lastResult));
}

void myWindow::Div(){
  lastResult = c->temp1/c->temp2;
  CentralText->append(QString::number(c->temp1)+"/"+QString::number(c->temp2)+"="+QString::number(lastResult));
}
void myWindow::Calc(){
  c->setVisible(!c->isVisible());
}

 
void myWindow::fileOpen(){
  QString name = QFileDialog::getOpenFileName(this,"open file","Choose a file to open");
  if (QFile::exists(name)){
    QFile file(name);
    if ( file.open(QIODevice::ReadOnly)){
       lastResult = QString(file.readLine()).toDouble();
       resultLabel->setText(QString::number(lastResult));
       CentralText->setText(QString(file.readAll()));
       myName = name;
       nameLabel->setText("File Name: " + myName.section('/',-1)); 
      file.close();
    }
    c->temp1 = lastResult;
    c->znak = -2;
    c->What();
  }
}
   
void myWindow::fileSave(){
  if(myName.isEmpty()){
     myName = QFileDialog::getSaveFileName(this,"Save file");
  }

  if(!myName.isEmpty()){
    QFile file(myName);
    if (file.open(QIODevice::WriteOnly)){
      QTextStream stream(&file);
      stream<<QString::number(lastResult)<<"\n"<< CentralText->toPlainText();
     // QString str = QString::number(lastResult) + "\n";
          //  file.write(str);
            //file.write(CentralText->Text());
       nameLabel->setText("File Name: " + myName.section('/',-1));
       file.close();
        }
    }
}

void myWindow::fileRevert(){
  if(!myName.isEmpty()){
    if(QFile::exists(myName)){
      QFile file(myName);
      if (file.open(QIODevice::ReadOnly)){
        lastResult = QString(file.readLine()).toDouble();
        resultLabel->setText(QString::number(lastResult));
        CentralText->setText(QString(file.readAll()));
        resultLabel->setText("Last Result: " + QString::number(lastResult));
        file.close();
      }
    }
  }
  c->temp1 = lastResult;
  c->znak = -2;
  c->What();
}

