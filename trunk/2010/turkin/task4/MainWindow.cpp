#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QIntValidator>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QTextEdit>
#include <QSettings>
#include <QFile>
#include <QTextStream>
#include <QByteArray>
#include <QIcon>

#include "MainWindow.h"
#include "CalcDialog.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    calcDialog = new CalcDialog(this);
    
    createStatusBar();
    createActions();
    createMenu();
    createToolBar();
    createCentralWidget();
    loadSettings();
    createConnects();
    
    logHistory = "";
    resultHistory = "0";
   	
}

MainWindow::~MainWindow() {
    saveSettings();
}

void MainWindow::createConnects() {
    connect( actOpenFile, SIGNAL(triggered()), this, SLOT(slotOpenFile()) );    
    connect( actSaveFile, SIGNAL(triggered()), this, SLOT(slotSaveFile()) );
    connect( actRevertFile, SIGNAL(triggered()), this, SLOT(slotRevertFile()) );
    connect( actShowCalc, SIGNAL(triggered(bool)), this, SLOT(slotShowCalc(bool)) );
    connect( calcDialog, SIGNAL(expr(double,char,double,double)), this, SLOT(exprCalculated(double,char,double,double)));
    connect( calcDialog, SIGNAL(calcHide(bool)), actShowCalc, SLOT(setChecked (bool)));
  	
}

void MainWindow::loadSettings() {
    QSettings settings("turkin", "task4");
    setGeometry( settings.value("geometry" , QRect(400,200, 350,420)).toRect() ); 
    if ( settings.contains("calc_geometry") ) {
        calcDialog->setGeometry( settings.value("calc_geometry").toRect() ); 
    }
}

void MainWindow::saveSettings() {
    QSettings settings("turkin", "task4");
    settings.setValue("geometry", geometry() );
    settings.setValue("calc_geometry", calcDialog->geometry() );
}


void MainWindow::createActions() {
    actOpenFile = new QAction("&Open",this);
    actSaveFile = new QAction("&Save",this);
    actRevertFile = new QAction("&Revert",this);
    actShowCalc = new QAction(QIcon(":/calc.svg"),"&Calculator",this);
    actShowCalc->setCheckable(true);
}

void MainWindow::createToolBar() {
    QToolBar* toolbar = new QToolBar("toolbar");
    toolbar->addAction(actShowCalc);
    addToolBar(toolbar);
}

void MainWindow::createMenu() {
    QMenu* menuFile = new QMenu("&File");
    QMenu* menuTools = new QMenu("&Tools");

    menuFile->addAction(actOpenFile);
    menuFile->addAction(actSaveFile);
    menuFile->addAction(actRevertFile);
    menuTools->addAction(actShowCalc);
    menuBar()->addMenu(menuFile);
    menuBar()->addMenu(menuTools);
}

void MainWindow::createStatusBar() {
    lblFilename = new QLabel("");
    lblResult = new QLabel("0");
    statusBar()->addWidget(lblFilename);
    statusBar()->addPermanentWidget(lblResult);
}

void MainWindow::createCentralWidget() {
	teLog =  new QTextEdit(this);
	teLog->setReadOnly(true);
	setCentralWidget( teLog );
}

void MainWindow::slotOpenFile() {
    QString filename = QFileDialog::getOpenFileName(this);
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    
    lblFilename->setText( file.fileName() );
    QTextStream stream(&file);  
    resultHistory = stream.readLine();
    lblResult->setText( resultHistory );   
    logHistory = ""; 
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        logHistory += line + "\n";
    }
    file.close();

    teLog->setPlainText( logHistory );
    calcDialog->setResult( resultHistory.toDouble() );
}

void MainWindow::slotSaveFile() { 
    QString filename;
    if (lblFilename->text() != "") {
        filename = lblFilename->text();
    } else {
        filename = QFileDialog::getSaveFileName(this);
    }
    QFile file(filename);
    if ( !file.open( QIODevice::WriteOnly | QIODevice::Text ) ) {
        return;
    }
    QTextStream stream(&file);
    stream << lblResult->text() << "\n";
    stream << teLog->toPlainText();
    logHistory = teLog->toPlainText();
    resultHistory = lblResult->text();
    lblFilename->setText( filename );
    file.close();   
}

void MainWindow::slotRevertFile() {
    teLog->setPlainText( logHistory );
    lblResult->setText( resultHistory );
    calcDialog->setResult( resultHistory.toInt() );
}

void MainWindow::slotShowCalc(bool checked) {
	calcDialog->setVisible(checked);
}

void MainWindow::exprCalculated(double operand1, char operation, double operand2, double result) {
    QString expr = QString("%1 %2 %3 = %4").arg(operand1).arg(operation).arg(operand2).arg(result);
    teLog->setPlainText( teLog->toPlainText() + expr + "\n");
    lblResult->setText( QString::number(result) );
}
