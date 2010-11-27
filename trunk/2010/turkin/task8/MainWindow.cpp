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

    ui.setupUi(this);

    calcDialog = new CalcDialog(this);
    setStatusBar();

    loadSettings();
    createConnects();
    
    logHistory = "";
    resultHistory = "0";
   	
}

MainWindow::~MainWindow() {
    saveSettings();
}

void MainWindow::createConnects() {
     connect( calcDialog, SIGNAL(expr(double,char,double,double)), this, SLOT(exprCalculated(double,char,double,double)));
     connect( calcDialog, SIGNAL(calcHide(bool)), ui.actShowCalc, SLOT(setChecked (bool)));  	
}

void MainWindow::loadSettings() {
    QSettings settings("turkin", "task8");
    setGeometry( settings.value("geometry" , QRect(400,200, 350,420)).toRect() );
    if ( settings.contains("calc_geometry") ) {
        calcDialog->setGeometry( settings.value("calc_geometry").toRect() );
    }
}

void MainWindow::saveSettings() {
    QSettings settings("turkin", "task8");
    settings.setValue("geometry", geometry() );
    settings.setValue("calc_geometry", calcDialog->geometry() );
}


void MainWindow::setStatusBar() {
    lblFilename = new QLabel("");
    lblResult = new QLabel("0");
    statusBar()->addWidget(lblFilename);
    statusBar()->addPermanentWidget(lblResult);
}


void MainWindow::on_actOpenFile_triggered() {
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

        ui.teLog->setPlainText( logHistory );
        calcDialog->setResult( resultHistory.toDouble() );
}

void MainWindow::on_actSaveFile_triggered() {
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
    stream << ui.teLog->toPlainText();
    logHistory = ui.teLog->toPlainText();
    resultHistory = lblResult->text();
    lblFilename->setText( filename );
    file.close();
}

void MainWindow::on_actRevertFile_triggered() {
    ui.teLog->setPlainText( logHistory );
    lblResult->setText( resultHistory );
    calcDialog->setResult( resultHistory.toInt() );
}

void MainWindow::on_actShowCalc_triggered(bool checked) {
        calcDialog->setVisible(checked);
}

void MainWindow::exprCalculated(double operand1, char operation, double operand2, double result) {
    QString expr = QString("%1 %2 %3 = %4").arg(operand1).arg(operation).arg(operand2).arg(result);
    ui.teLog->setPlainText( ui.teLog->toPlainText() + expr + "\n");
    lblResult->setText( QString::number(result) );
}
