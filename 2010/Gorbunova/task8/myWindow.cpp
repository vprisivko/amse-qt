#include "myWindow.h"
#include "ui_myWindow.h"
#include <QMenuBar>
#include <QAction>
#include <QStatusBar>
#include <QSettings>
#include <QToolBar>
#include <QFileDialog>
#include <QTextEdit>
#include <QTextStream>
#include <QStringList>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myName = "";
     nameLabel = new QLabel("File Name: "+myName,this);
     lastResult = 0;
     resultLabel = new QLabel("Last Result : "+QString::number(lastResult));
     c = new myCalc(this);
     statusBar()->addWidget(nameLabel,1);
     statusBar()->addWidget(resultLabel,1);
     connection();

}
void MainWindow::connection(){
      connect(ui->actionCalcul_2 , SIGNAL(triggered()), this, SLOT(Calc()));
      connect(c, SIGNAL(signalAdd()),this, SLOT(Add()));
      connect(c, SIGNAL(signalSub()),this, SLOT(Sub()));
      connect(c, SIGNAL(signalMul()),this, SLOT(Mul()));
      connect(c, SIGNAL(signalDiv()),this, SLOT(Div()));
      connect(ui->actionOpen_2, SIGNAL(triggered()), this, SLOT(fileOpen()));
      connect(ui->actionSave_2, SIGNAL(triggered()), this, SLOT(fileSave()));
      connect(ui->actionRevert_2, SIGNAL(triggered()), this, SLOT(fileRevert()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }

}

void MainWindow::Add(){
  lastResult = c->temp1+c->temp2;
  ui->textBrowser->append(QString::number(c->temp1)+"+"+QString::number(c->temp2)+"="+QString::number(lastResult));
}

void MainWindow::Sub(){
  lastResult = c->temp1-c->temp2;
  ui->textBrowser->append(QString::number(c->temp1)+"-"+QString::number(c->temp2)+"="+QString::number(lastResult));
}

void MainWindow::Mul(){
  lastResult = c->temp1*c->temp2;
  ui->textBrowser->append(QString::number(c->temp1)+"*"+QString::number(c->temp2)+"="+QString::number(lastResult));
}

void MainWindow::Div(){
  lastResult = c->temp1/c->temp2;
  ui->textBrowser->append(QString::number(c->temp1)+"/"+QString::number(c->temp2)+"="+QString::number(lastResult));
}
void MainWindow::Calc(){
  c->setVisible(!c->isVisible());
}


void MainWindow::fileOpen(){
  QString name = QFileDialog::getOpenFileName(this,"open file","Choose a file to open");
  if (QFile::exists(name)){
    QFile file(name);
    if ( file.open(QIODevice::ReadOnly)){
       lastResult = QString(file.readLine()).toDouble();
       resultLabel->setText(QString::number(lastResult));
       ui->textBrowser->setText(QString(file.readAll()));
       myName = name;
       nameLabel->setText("File Name: " + myName.section('/',-1));
      file.close();
    }
    c->temp1 = lastResult;
    c->znak = -2;
    c->What();
  }
}

void MainWindow::fileSave(){
  if(myName.isEmpty()){
     myName = QFileDialog::getSaveFileName(this,"Save file");
  }

  if(!myName.isEmpty()){
    QFile file(myName);
    if (file.open(QIODevice::WriteOnly)){
      QTextStream stream(&file);
      stream<<QString::number(lastResult)<<"\n"<< ui->textBrowser->toPlainText();
     // QString str = QString::number(lastResult) + "\n";
          //  file.write(str);
            //file.write(CentralText->Text());
       nameLabel->setText("File Name: " + myName.section('/',-1));
       file.close();
        }
    }
}

void MainWindow::fileRevert(){
  if(!myName.isEmpty()){
    if(QFile::exists(myName)){
      QFile file(myName);
      if (file.open(QIODevice::ReadOnly)){
        lastResult = QString(file.readLine()).toDouble();
        resultLabel->setText(QString::number(lastResult));
        ui->textBrowser->setText(QString(file.readAll()));
        resultLabel->setText("Last Result: " + QString::number(lastResult));
        file.close();
      }
    }
  }
  c->temp1 = lastResult;
  c->znak = -2;
  c->What();
}

