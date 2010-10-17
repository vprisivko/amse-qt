#include"MyMainWindow.h"
#include<QLayout>
#include<QString>
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QDebug>
#include<QSettings>
MyMainWindow::MyMainWindow(){
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
MyMainWindow::~MyMainWindow() {
      settings->beginGroup("CalcMainWind");
      settings->setValue("geomerty", calcDialog->geometry());
      settings->endGroup();

}

void MyMainWindow::createWidgets() {
    currentFile = "";
    fileMenu = new QMenu("&File",this);
    toolMenu = new QMenu("&Tools", this);
    toolBar = new QToolBar(this);
    nameLog = new QLabel(QString("File name: "), this);
    resultLabel = new QLabel(QString("last result:"), this);
    open = new QAction("&Open",fileMenu);
    save = new QAction("&Save",fileMenu);
    revert = new QAction("&Revert",fileMenu);
    calculator = new QAction("&Calculator",toolMenu);
    calcDialog = new Calculator(0,this);
    centralLog = new QTextEdit(this);
    centralLog->setReadOnly(true);
    calculator->setCheckable(true);
}

void MyMainWindow::addWidgets(){
    fileMenu->addAction(open);
    fileMenu->addAction(save);
    fileMenu->addAction(revert);
    toolMenu->addAction(calculator);
    toolBar->addAction(calculator);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(toolMenu);
    this->addToolBar(toolBar);
    statusBar()->addWidget(nameLog);
    statusBar()->addWidget(resultLabel);
     this->setCentralWidget(centralLog);
}
void MyMainWindow::connectWidgets() {

connect( open, SIGNAL(triggered()), this, SLOT(openFile()) );
connect( save, SIGNAL(triggered()), this, SLOT(saveFile()) );
connect( revert, SIGNAL(triggered()), this, SLOT(revertFile()) );
connect( calculator, SIGNAL(triggered(bool)), this, SLOT(showCalc(bool)) );
connect(calcDialog,SIGNAL(newexpr(QString,double)),this,SLOT(writeCalcLine(QString,double)));

}

void MyMainWindow::showCalc(bool vis) {
    calcDialog->setVisible(vis);
}

void MyMainWindow::writeCalcLine(QString str, double res){
    centralLog->setText(centralLog->toPlainText() +str+ "\n");
    resultLabel->setText(QString::number(res));
}

void MyMainWindow::openFile(){
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
      centralLog->setPlainText(QString(fdata+i+1));
      historyFile = QString(fdata+i);
      fin.close();
}

void MyMainWindow::saveFile(){
    QString filename = currentFile;
      if (currentFile == "") {
        filename = QFileDialog::getSaveFileName(this);
      }
      QFile fout(filename);
      if (!fout.open(QIODevice::WriteOnly | QIODevice::Text)) return;
      QTextStream foutStream(&fout);
      //fout.write(QByteArray((resultLabel->text() + "\n").toAscii()).data());
      //fout.write(QByteArray(centralLog->toPlainText().toAscii()).data());
      historyFile = centralLog->toPlainText();
      fileResult = resultLabel->text();

      foutStream<< resultLabel->text() + "\n";
      foutStream<< centralLog->toPlainText();
      currentFile = filename;
      nameLog->setText(filename);
      fout.close();
}


void MyMainWindow::revertFile(){
    centralLog->setPlainText(historyFile);
    resultLabel->setText(fileResult);

    calcDialog->result = fileResult.toDouble();


}
