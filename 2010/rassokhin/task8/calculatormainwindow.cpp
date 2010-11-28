#include "calculatormainwindow.h"
#include "ui_calculatormainwindow.h"


#include <QMenuBar>
#include <QStatusBar>
#include <QApplication>
#include <QFileDialog>
#include <QLayout>
#include <QMessageBox>
#include <QTextStream>
#include <QVBoxLayout>

CalculatorMainWindow::CalculatorMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CalculatorMainWindow), calcDialog(0),
        logName("noname.calc.log"), lastStateLastOpResult(0), lastOpResult(0) {
    ui->setupUi(this);
    loadSettings();
    fixUi();
    connectSignals();
    updateStatusBar();
}

CalculatorMainWindow::~CalculatorMainWindow() {\
    delete ui;
}

void CalculatorMainWindow::loadSettings() {
    settings = new QSettings("ru.amse.qt2010.rassokhin","loggedcalc",this);
    settings->beginGroup("CalculatorMainWindow");
    resize( settings->value("size",     QSize (320, 240) ).toSize());
    move(   settings->value("position", QPoint(120, 160) ).toPoint());
    settings->endGroup();
}

void CalculatorMainWindow::closeEvent(QCloseEvent *) {
    saveSettings();
}

void CalculatorMainWindow::saveSettings() {
    settings->beginGroup("CalculatorMainWindow");
    settings->setValue("size",     size());
    settings->setValue("position", pos());
    settings->endGroup();
}

void CalculatorMainWindow::fixUi() {
    ui->actionOpen->setShortcuts(QKeySequence::Open);
    ui->actionSave->setShortcuts(QKeySequence::Save);
    ui->actionQuit->setShortcuts(QKeySequence::Quit);

    //status bar
    statusBar()->insertWidget(0, ui->sbFileName);
    statusBar()->insertPermanentWidget(1, ui->sbLastOpResult);
}

void CalculatorMainWindow::connectSignals() {
    connect(ui->actionOpen,   SIGNAL( triggered() ), SLOT( fileOpen() ));
    connect(ui->actionSave,   SIGNAL( triggered() ), SLOT( fileSave() ));
    connect(ui->actionRevert, SIGNAL( triggered() ), SLOT( fileRevert() ));
    connect(ui->actionQuit,   SIGNAL( triggered() ), qApp, SLOT( quit() ));
    connect(ui->actionCalculator, SIGNAL( triggered() ), SLOT( toggleCalc() ));
}

void CalculatorMainWindow::fileOpen() {
    QString newFileName = QFileDialog::getOpenFileName(this, tr("Open log"),
            QDir::homePath(), tr("Calc log files(*.calc.log);;All files(*.*)") );
    if (newFileName == QString::null) return;
    logName = newFileName;
    ui->sbFileName->setText(logName);
    loadLog(logName);
    updateStatusBar();
}

void CalculatorMainWindow::fileSave() {
    if (ui->logText->toPlainText().isEmpty() ) return;
    QString saveFileName = QFileDialog::getSaveFileName(this, tr("Save log"),
            QDir::homePath(), tr("Calc log files(*.calc.log);;All files(*.*)") );
    if (saveFileName.isEmpty()) return;
    saveLog(saveFileName);
}

void CalculatorMainWindow::fileRevert() {
   ui->logText->setPlainText(lastState);
   lastOpResult = lastStateLastOpResult;
   if(calcDialog != 0) calcDialog->setLastOpResult(lastOpResult);
   updateStatusBar();
}

void CalculatorMainWindow::toggleCalc() {
    if(calcDialog == 0) initCalculatorDialog();
    calcDialog->setVisible(!calcDialog->isVisible());
}

void CalculatorMainWindow::updateStatusBar() {
    ui->sbFileName->setText(logName);
    ui->sbLastOpResult->setText(QString::number(lastOpResult));
}

void CalculatorMainWindow::calculate(QString str, qreal result) {
    ui->logText->appendPlainText(str);
    lastOpResult = result;
    updateStatusBar();
}

void CalculatorMainWindow::initCalculatorDialog() {
    if(calcDialog != 0) return;
    calcDialog = new CalculatorDialog(this);
    calcDialog->setLastOpResult(lastOpResult);
    connect(calcDialog, SIGNAL(calculated(QString, qreal)), this,
            SLOT(calculate(QString, qreal)));
}

void CalculatorMainWindow::loadLog(QString fileName) {
    QFile loadFile(fileName, this);
    if(!loadFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, this->windowTitle(), "Cannot load log from file: " + fileName + "\nCannot open file.");
        return;
    }
    { // this block for destruct QTextStream before closing QFile
        QTextStream ts(&loadFile);
        if (ts.atEnd()) {
            lastOpResult = 0;
            ui->logText->setPlainText(QString());
        }
        bool result;
        qreal tmp = ts.readLine().toDouble(&result);
        if(!result) {
            QMessageBox::warning(this,this->windowTitle(),"Cannot load log from file: " + fileName + "\nStrange file format.");
            loadFile.close();
            return;
        }
        lastStateLastOpResult = tmp;
        lastState = ts.readAll();
        fileRevert();
    }
    loadFile.close();
}

void CalculatorMainWindow::saveLog(QString fileName) {
    QFile saveFile(fileName,this);
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this,this->windowTitle(),"Cannot save log to file: " + fileName);
        return;
    }
    { // this block for destruct QTextStream before closing QFile
        QTextStream ts(&saveFile);
        lastStateLastOpResult = lastOpResult;
        lastState = ui->logText->toPlainText();
        ts << QString::number(lastStateLastOpResult) << "\n";
        ts << lastState;
    }
    saveFile.close();
}

void CalculatorMainWindow::changeEvent(QEvent *e) {
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

