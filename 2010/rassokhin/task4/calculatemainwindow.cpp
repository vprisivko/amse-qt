#include "calculatemainwindow.h"

#include <QMenuBar>
#include <QStatusBar>
#include <QApplication>
#include <QFileDialog>
#include <QLayout>
#include <QMessageBox>
#include <QTextStream>
#include <QVBoxLayout>

CalculateMainWindow::CalculateMainWindow(QWidget *parent)
    : QMainWindow(parent), calcDialog(0), logName("noname.calc.log"),
                lastStateLastOpResult(0), lastOpResult(0) {
    setWindowTitle(tr("Calculator with log"));
    loadSettings();
    constructObjects();
    connectSignals();
    updateStatusBar();
}

void CalculateMainWindow::loadSettings() {
    settings = new QSettings("ru.amse.qt2010.rassokhin","loggedcalc",this);
    settings->beginGroup("CalculateMainWindow");
    resize( settings->value("size",     QSize (320, 240) ).toSize());
    move(   settings->value("position", QPoint(120, 160) ).toPoint());
    settings->endGroup();
}

void CalculateMainWindow::closeEvent(QCloseEvent *) {
    saveSettings();
}

void CalculateMainWindow::saveSettings() {
    settings->beginGroup("CalculateMainWindow");
    settings->setValue("size",     size());
    settings->setValue("position", pos());
    settings->endGroup();
}

void CalculateMainWindow::constructObjects() {
    // log text
    logText = new QPlainTextEdit(this);
    setCentralWidget(logText);
    logText->setReadOnly(true);

    //actions
    actionOpen = new QAction(tr("&Open"), this);
    actionSave = new QAction(tr("&Save"), this);
    actionRevert = new QAction(tr("&Revert"), this);
    actionToggleCalcDialog = new QAction(tr("&Calculator"), this);
    actionQuit = new QAction(tr("&Quit"), this);

    actionOpen->setShortcuts(QKeySequence::Open);
    actionSave->setShortcuts(QKeySequence::Save);
    actionQuit->setShortcuts(QKeySequence::Quit);

    //menus
    menuFile = menuBar()->addMenu(tr("&File"));
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionRevert);
    menuFile->addAction(actionQuit);
    menuBar()->addAction(actionToggleCalcDialog);

    //status bar
    sbFileName = new QLabel(this);
    sbLastOpResult = new QLabel(this);
    statusBar()->insertWidget(0,sbFileName);
    statusBar()->insertPermanentWidget(1,sbLastOpResult);
}

void CalculateMainWindow::connectSignals() {
    connect(actionOpen,   SIGNAL( triggered() ), SLOT( fileOpen() ));
    connect(actionSave,   SIGNAL( triggered() ), SLOT( fileSave() ));
    connect(actionRevert, SIGNAL( triggered() ), SLOT( fileRevert() ));
    connect(actionQuit,   SIGNAL( triggered() ), qApp, SLOT( quit() ));
    connect(actionToggleCalcDialog, SIGNAL( triggered() ), SLOT( toggleCalc() ));
}

void CalculateMainWindow::fileOpen() {
    QString newFileName = QFileDialog::getOpenFileName(this, tr("Open log"),
            QDir::homePath(), tr("Calc log files (*.calc.log)") );
    if (newFileName == QString::null) return;
    logName = newFileName;
    sbFileName->setText(logName);
    loadLog(logName);
    updateStatusBar();
}

void CalculateMainWindow::fileSave() {
    if (logText->toPlainText().isEmpty() ) return;
    QString saveFileName = QFileDialog::getSaveFileName(this, tr("Save log"),
            QDir::homePath(), tr("Calc log files (*.calc.log)") );
    if (saveFileName.isEmpty()) return;
    saveLog(saveFileName);
}

void CalculateMainWindow::fileRevert() {
   logText->setPlainText(lastState);
   lastOpResult = lastStateLastOpResult;
   if(calcDialog != 0) calcDialog->setLastOpResult(lastOpResult);
   updateStatusBar();
}

void CalculateMainWindow::toggleCalc() {
    if(calcDialog == 0) initCalculatorDialog();
    calcDialog->setVisible(!calcDialog->isVisible());
}

void CalculateMainWindow::updateStatusBar() {
    sbFileName->setText(logName);
    sbLastOpResult->setText(QString::number(lastOpResult));
}

void CalculateMainWindow::calculate(QString str, qreal result) {
    logText->appendPlainText(str);
    lastOpResult = result;
    updateStatusBar();
}

void CalculateMainWindow::initCalculatorDialog() {
    if(calcDialog != 0) return;
    calcDialog = new CalculatorDialog(this);
    calcDialog->setLastOpResult(lastOpResult);
    connect(calcDialog,SIGNAL(calculated(QString,qreal)),this,SLOT(calculate(QString,qreal)));
}

void CalculateMainWindow::loadLog(QString fileName) {
    QFile loadFile(fileName,this);
    if(!loadFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this,this->windowTitle(),"Cannot load log from file: " + fileName + "\nCannot open file.");
        return;
    }
    { // this block for destruct QTextStream before closing QFile
        QTextStream ts(&loadFile);
        if (ts.atEnd()) {
            lastOpResult = 0;
            logText->setPlainText(QString());
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

void CalculateMainWindow::saveLog(QString fileName) {
    QFile saveFile(fileName,this);
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this,this->windowTitle(),"Cannot save log to file: " + fileName);
        return;
    }
    { // this block for destruct QTextStream before closing QFile
        QTextStream ts(&saveFile);
        lastStateLastOpResult = lastOpResult;
        lastState = logText->toPlainText();
        ts << QString::number(lastStateLastOpResult) << "\n";
        ts << lastState;
    }
    saveFile.close();
}

