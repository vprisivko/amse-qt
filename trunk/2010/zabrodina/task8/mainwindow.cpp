#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createWidgets();
    addWidgets();
    connectWidgets();
    fileResult = "0" ;
    historyFile = "";
    settings = new QSettings ("zabrodina","task4",this);
    settings->beginGroup("CalcMainWind");
    calcDialog->setGeometry(settings->value("geomerty",QRect(400,400, 200,200)).toRect() );
    settings->endGroup();
}

MainWindow::~MainWindow()
{
    delete ui;
    settings->beginGroup("CalcMainWind");
    settings->setValue("geomerty", calcDialog->geometry());
    settings->endGroup();

}

void MainWindow::createWidgets() {
    currentFile = "";
    nameLog = new QLabel(QString("File name: "), this);
    resultLabel = new QLabel(QString("last result:"), this);
    calcDialog = new Calculator(0,this);

}

void MainWindow::addWidgets(){

    statusBar()->addWidget(nameLog);
    statusBar()->addWidget(resultLabel);
    this->setCentralWidget(ui->centralLog);
    ui->mainToolBar->addAction(ui->actionCalculator);
}
void MainWindow::connectWidgets() {

connect( ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()) );
connect( ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()) );
connect( ui->actionRevert, SIGNAL(triggered()), this, SLOT(revertFile()) );
connect( ui->actionCalculator, SIGNAL(triggered(bool)), this, SLOT(showCalc(bool)) );
connect(calcDialog,SIGNAL(newexpr(QString,double)),this,SLOT(writeCalcLine(QString,double)));

}

void MainWindow::showCalc(bool vis) {
    calcDialog->setVisible(vis);
}

void MainWindow::writeCalcLine(QString str, double res){
    ui->centralLog->setText(ui->centralLog->toPlainText() +str+ "\n");
    resultLabel->setText(QString::number(res));
}

void MainWindow::openFile(){
    QString filename = QFileDialog::getOpenFileName(this);
    QFile fin(filename);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    currentFile = filename;
    nameLog->setText(filename);
    const char * fdata = (const char *)fin.map(0, fin.size());
      int i = 0;
      fileResult = "";
      while (fdata[i] != '\n') {
        fileResult += fdata[i];
        ++i;
      }
      resultLabel->setText(fileResult);
      calcDialog->result = fileResult.toDouble();
      ui->centralLog->setPlainText(QString(fdata+i+1));
      historyFile = QString(fdata+i);
      fin.close();
}

void MainWindow::saveFile(){
    QString filename = currentFile;
      if (currentFile == "") {
        filename = QFileDialog::getSaveFileName(this);
      }
      QFile fout(filename);
      if (!fout.open(QIODevice::WriteOnly | QIODevice::Text)) return;
      QTextStream foutStream(&fout);
      //fout.write(QByteArray((resultLabel->text() + "\n").toAscii()).data());
      //fout.write(QByteArray(centralLog->toPlainText().toAscii()).data());
      historyFile = ui->centralLog->toPlainText();
      fileResult = resultLabel->text();

      foutStream<< resultLabel->text() + "\n";
      foutStream<< ui->centralLog->toPlainText();
      currentFile = filename;
      nameLog->setText(filename);
      fout.close();
}


void MainWindow::revertFile(){
    ui->centralLog->setPlainText(historyFile);
    resultLabel->setText(fileResult);

    calcDialog->result = fileResult.toDouble();


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
