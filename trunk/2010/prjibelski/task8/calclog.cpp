#include <QFileDialog>

#include "calclog.h"
#include "ui_calclog.h"

CalcLog::CalcLog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CalcLog)
{
    ui->setupUi(this);

    calcDialog = new CalcDialog(this);
    currentFileName = "";

    fileNameLabel = new QLabel("Current file: ", this->statusBar());
    lastResultLabel = new QLabel("Last result: ", this->statusBar());
    ui->statusBar->addWidget(fileNameLabel);
    ui->statusBar->addWidget(lastResultLabel);

    this->setCentralWidget(ui->calcLog);

    connectSlots();
}

CalcLog::~CalcLog()
{
    delete ui;
}


void CalcLog::connectSlots() {
    connect( calcDialog, SIGNAL( newString(QString, double) ), this, SLOT( addString(QString, double) ) );

    connect( ui->saveFileAction, SIGNAL( triggered() ), this, SLOT(saveFileSlot()) );
    connect( ui->saveCurrentFileAction, SIGNAL( triggered() ), this, SLOT(saveCurrentFileSlot()) );
    connect( ui->openFileAction, SIGNAL( triggered() ), this, SLOT(openFileSlot()) );
    connect( ui->revertFileAction, SIGNAL( triggered() ), this, SLOT(revertSlot()) );

    connect( ui->showCalcAction, SIGNAL( triggered() ), this, SLOT(showCalcDialogSlot()) );

    connect( calcDialog, SIGNAL(dialogClosed()), this, SLOT(caclClosed()) );
 }

void CalcLog::caclClosed() {
    if ( calcDialog->isVisible() ) {
        ui->showCalcAction->setChecked(false);
    }
    else {
        ui->showCalcAction->setChecked(true);
    }
}

void CalcLog::showCalcDialogSlot() {

    if ( calcDialog->isVisible() ) {
        calcDialog->hide();
        ui->showCalcAction->setChecked(false);
    }
    else {
        calcDialog->show();
        ui->showCalcAction->setChecked(true);
    }
}

void CalcLog::updateStatusBar() {
    fileNameLabel->setText("Current file: " + currentFileName );

    lastResultLabel->setText("Last result: " + QString::number(lastResult));
}

void CalcLog::addString(QString logString, double result) {
    ui->calcLog->append(logString);
    lastResult = result;
    updateStatusBar();
}


void CalcLog::openFileSlot() {
    loadFromFile( QFileDialog::getOpenFileName(this) );
}

void CalcLog::saveCurrentFileSlot() {
    if (currentFileName == "") {
        saveFileSlot();
    }
    else {
        saveToFile(currentFileName);
    }
}

void CalcLog::saveFileSlot() {
    saveToFile( QFileDialog::getSaveFileName(this) );
}

void CalcLog::saveToFile( QString fileName ) {
    QFile outFile(fileName);
    if ( !outFile.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    currentFileName = fileName;
    updateStatusBar();

    QTextStream outStream(&outFile);
    outStream << QString::number( lastResult ) << "\n" << ui->calcLog->toPlainText();

    outFile.close();
}

void CalcLog::loadFromFile( QString fileName ) {
    QFile inFile(fileName);

    if ( !inFile.open( QIODevice::ReadOnly | QIODevice::Text ) ) return;

    currentFileName = fileName;
    QTextStream inStream(&inFile);
    inStream >> lastResult;
    updateStatusBar();
    calcDialog->setCurrentValue(lastResult);

    inStream.readLine(2);

    ui->calcLog->setText( inStream.readAll() );
}

void CalcLog::revertSlot() {
    if (currentFileName == "") {
        ui->calcLog->setText("");
        lastResult = 0.0;
        calcDialog->setCurrentValue(0);
        updateStatusBar();
    }
    else {
        loadFromFile(currentFileName);
    }
}



