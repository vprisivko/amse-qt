#include <QLabel>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    logName= new QLabel("untitled.log");
    lastResult = new QLabel("0");

    statusBar()->addWidget(new QLabel("Log name:"));
    statusBar()->addWidget(logName);
    statusBar()->addWidget(new QLabel("Last result:"));
    statusBar()->addWidget(lastResult);

    ui->menuView->addAction(ui->dockCalc->toggleViewAction());
    myResult = 0;
}


void MainWindow::plusPressed(){

    double b = QString(ui->myInput->text()).toDouble();
    QString newCalc = QString::number(myResult).append(" + ").append(QString::number(b)).append(" = ")
            .append(QString::number(myResult + b));
    myResult += b;
    ui->myTextEdit->appendPlainText(newCalc);

}

void MainWindow::minusPressed(){

    double b = QString(ui->myInput->text()).toDouble();
    QString newCalc = QString::number(myResult).append(" - ").append(QString::number(b)).append(" = ")
            .append(QString::number(myResult - b));
    myResult -= b;
    ui->myTextEdit->appendPlainText(newCalc);

}

void MainWindow::multPressed(){

    double b = QString(ui->myInput->text()).toDouble();
    QString newCalc = QString::number(myResult).append(" * ").append(QString::number(b)).append(" = ")
            .append(QString::number(myResult * b));
    myResult *= b;
    ui->myTextEdit->appendPlainText(newCalc);

}

void MainWindow::dividePressed(){

    double b = QString(ui->myInput->text()).toDouble();
    QString newCalc = QString::number(myResult).append(" / ").append(QString::number(b)).append(" = ")
            .append(QString::number(myResult / b));
    myResult /= b;
    ui->myTextEdit->appendPlainText(newCalc);

}

void MainWindow::documentWasModified(){

    lastResult->setText(QString::number(myResult));

}

void MainWindow::newFile(){

    curFile = "";
    ui->myTextEdit->setPlainText("");
    myResult = 0;
    logName->setText("untitled.log");
    lastResult->setText(QString::number(myResult));

}


void MainWindow::revert(){
    if(!curFile.isEmpty()) {
     loadFile(curFile);
    }
    else{
        ui->myTextEdit->setPlainText("");
        myResult=0;
        lastResult->setText(QString::number(myResult));
    }
}

bool MainWindow::save(){

    if (curFile.isEmpty())
        return saveAs();
    else
        return saveFile(curFile);

}

bool MainWindow::saveAs(){

    QString fileName = QFileDialog::getSaveFileName(this, "Save log");
    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);

}

void MainWindow::open(){

    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadFile(fileName);

}

bool MainWindow::saveFile(const QString &fileName){

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Logger", "Cannot write file!");
        return false;
    }
    QTextStream out(&file);
    out << myResult << "\n";
    out << ui->myTextEdit->toPlainText();
    curFile = fileName;
    logName->setText(curFile);
    return true;

 }

void MainWindow::loadFile(const QString &fileName){

     QFile file(fileName);
     if (!file.open(QFile::ReadOnly | QFile::Text)) {
         QMessageBox::warning(this, "Logger", "Cannot read file!");
         return;
     }

     QTextStream in(&file);
     myResult = in.readLine().toInt();
     lastResult->setText(QString::number(myResult));

     while(!in.atEnd())
        ui->myTextEdit->setPlainText(in.readAll());

     curFile = fileName;
     logName->setText(fileName);

 }


MainWindow::~MainWindow()
{
    delete ui;
}
