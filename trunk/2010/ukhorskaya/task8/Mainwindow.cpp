#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include "QMenuBar"
#include "QStatusBar"
#include "QMenu"
#include "QDebug"
#include "QVBoxLayout"
#include "QPushButton"
#include "QHBoxLayout"
#include "QFile"
#include "QFileDialog"
#include "QMessageBox"
#include "QScrollArea"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    calc = new Calculator(this);

//    createMenu();
//    createLogWidget();
    createStatusBar();

    connect(calc, SIGNAL(exprCalc(QString)), this, SLOT(exprCalculated(QString)));

    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(openFile(bool)));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionRevert, SIGNAL(triggered()), this, SLOT(revertFile()));

    connect(ui->actionCcc, SIGNAL(triggered()), this, SLOT(calcPressed()));

    fileName = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createStatusBar() {
    resultLabel = new QLabel("0");
    statusBar()->addWidget(resultLabel);
    fileNameLabel = new QLabel("no file selected");
    statusBar()->addWidget(fileNameLabel);
}

void MainWindow::openFile(bool revert) {
    //Is file opened or reverted
    if (!revert) {
        QFileDialog *fileDialog = new QFileDialog(this, "Select File");
        fileName = fileDialog->getOpenFileName();
    }

    QFile *file = new QFile(fileName);
    file->open(QIODevice::ReadOnly);

    //Last Value
    QString result = file->readLine();
    calc->lastValue = result.toDouble();

    //Log
    fileContent = file->readAll();

    ui->centralLabel->setText(fileContent);

    file->close();

    if (revert) {
        QMessageBox *fileClosed = new QMessageBox(this);
        fileClosed->information(this, "Information", "File reverted");
    }

    fileNameLabel->setText(fileName);
    resultLabel->setText(QString().number(calc->lastValue));
}

void MainWindow::saveFile() {
    if (fileName.isEmpty()) {
        fileName = QFileDialog( this, "Select file" ).getSaveFileName();
    }

    QFile *file = new QFile(fileName);
    file->open(QIODevice::WriteOnly);

    file->write(QString().number(calc->lastValue).toAscii());

    file->write("\n");
    file->write(fileContent.toAscii());

    file->close();

    QMessageBox *fileClosed = new QMessageBox(this);
    fileClosed->information(this, "Information", "File saved");
}

void MainWindow::revertFile() {
    if (fileName.isEmpty()) {
        QMessageBox *error = new QMessageBox(this);
        error->warning(this, "Error", "No selected file");
        return;
    }
    emit openFile(true);
}

void MainWindow::exprCalculated(QString result) {
    ui->centralLabel->setPlainText(ui->centralLabel->toPlainText() + result);
    resultLabel->setText(QString::number(calc->lastValue));
}

void MainWindow::calcPressed() {
     calc->setVisible(calc->isHidden());
}
