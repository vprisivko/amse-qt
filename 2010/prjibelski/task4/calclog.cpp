#include "calclog.h"

CalcLog::CalcLog(QWidget *parent)
    : QMainWindow(parent)
{
    createWindow();

    calcDialog = new CalcDialog(this);
    //fileDialog = new QFileDialog(this);
    //currentFile = new QFile();
    //currentStream = new QTextStream();

    currentFileName = "";
    connectSlots();
}

CalcLog::~CalcLog()
{

}

void CalcLog::createMenuBar() {
    QMenu* fileMenu = new QMenu("File", this->menuBar());
    openFileAction = new QAction("Open", fileMenu);
    saveFileAction = new QAction("Save as...", fileMenu);
    saveCurrentFileAction = new QAction("Save", fileMenu);
    revertAction = new QAction("Revert", fileMenu);
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(saveCurrentFileAction);
    fileMenu->addAction(saveFileAction);
    fileMenu->addAction(revertAction);

    showCalcAction = new QAction("Calculator", this->menuBar());
    showCalcAction->setCheckable(true);

    this->menuBar()->addMenu(fileMenu);
    this->menuBar()->addAction(showCalcAction);

}

void CalcLog::createWindow() {
    createMenuBar();

    calcLog = new QTextEdit( this );
    calcLog->setReadOnly(true);
    this->setCentralWidget(calcLog);

    fileNameLabel = new QLabel("Current file: ", this->statusBar());
    lastResultLabel = new QLabel("Last result: ", this->statusBar());
    this->statusBar()->addWidget(fileNameLabel);
    this->statusBar()->addWidget(lastResultLabel);
}

void CalcLog::connectSlots() {
    connect( calcDialog, SIGNAL( newString(QString, int) ), this, SLOT( addString(QString, int) ) );

    connect( saveFileAction, SIGNAL( triggered() ), this, SLOT(saveFileSlot()) );
    connect( saveCurrentFileAction, SIGNAL( triggered() ), this, SLOT(saveCurrentFileSlot()) );
    connect( openFileAction, SIGNAL( triggered() ), this, SLOT(openFileSlot()) );
    connect( revertAction, SIGNAL( triggered() ), this, SLOT(revertSlot()) );

    connect( showCalcAction, SIGNAL( triggered() ), this, SLOT(showCalcDialogSlot()) );
 }

void CalcLog::showCalcDialogSlot() {

    if ( calcDialog->isVisible() )
        calcDialog->hide();
    else
        calcDialog->show();

}

void CalcLog::updateStatusBar() {
    fileNameLabel->setText("Current file: " + currentFileName );

    lastResultLabel->setText("Last result: " + QString::number(lastResult));
}

void CalcLog::addString(QString logString, int result) {
    calcLog->append(logString);
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
    outStream << QString::number( lastResult ) << "\n" << calcLog->toPlainText();

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

    calcLog->setText( inStream.readAll() );
}

void CalcLog::revertSlot() {
    if (currentFileName == "") {
        calcLog->setText("");
        lastResult = 0;
        calcDialog->setCurrentValue(0);
        updateStatusBar();
    }
    else {
        loadFromFile(currentFileName);
    }
}



