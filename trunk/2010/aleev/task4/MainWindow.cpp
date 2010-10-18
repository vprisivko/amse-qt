#include "MainWindow.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QAction>
#include <QSettings>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), logHistory(""), lastResultHistory("0") {
    calc = new Calculator(this);
    filenameLabel = new QLabel("Unsaved file");
    lastResultLabel = new QLabel("0");
    statusBar()->addWidget(filenameLabel);
    statusBar()->addPermanentWidget(lastResultLabel);

    QAction *openFileAction = new QAction("&Open",this);
    QAction *saveFileAction = new QAction("&Save",this);
    QAction *revertFileAction = new QAction("&Revert",this);
    QAction *showCalculatorAction = new QAction("&Calculator",this);
    showCalculatorAction->setCheckable(true);
    menuBar()->addAction(openFileAction);
    menuBar()->addAction(saveFileAction);
    menuBar()->addAction(revertFileAction);
    menuBar()->addAction(showCalculatorAction);

    logTextEdit =  new QTextEdit(this);
    logTextEdit->setReadOnly(true);
    setCentralWidget(logTextEdit);

    connect(openFileAction, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    connect(saveFileAction, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    connect(revertFileAction, SIGNAL(triggered(bool)), this, SLOT(revertFile()));
    connect(showCalculatorAction, SIGNAL(triggered(bool)), this, SLOT(showCalculator(bool)));
    connect(calc, SIGNAL(toWrite(QString, double)), this, SLOT(addToLog(QString, double)));

    QSettings settings;
    setGeometry(settings.value("geometry", QRect(150, 150, 600, 500)).toRect());
}

void MainWindow::addToLog(QString str, double res) {
    logTextEdit->setPlainText(logTextEdit->toPlainText() + str + "\n");
    lastResultLabel->setText(QString::number(res));
}

void MainWindow::openFile() {
    QString filename = QFileDialog::getOpenFileName(this);
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    filenameLabel->setText(file.fileName());
    QTextStream stream(&file);
    lastResultHistory = stream.readLine();
    lastResultLabel->setText(lastResultHistory);
    logHistory = ""; 
    while (!stream.atEnd()) {
        QString curLine = stream.readLine();
        logHistory += curLine + "\n";
    }
    file.close();
    logTextEdit->setPlainText(logHistory);
    calc->myCurResult = lastResultHistory.toDouble();
}

void MainWindow::saveFile() {
    QString filename;
    filename = QFileDialog::getSaveFileName(this);
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QTextStream stream(&file);
    stream << lastResultLabel->text() << "\n";
    stream << logTextEdit->toPlainText();
    logHistory = logTextEdit->toPlainText();
    lastResultHistory = lastResultLabel->text();
    filenameLabel->setText(filename);
    file.close();
}

void MainWindow::revertFile() {
    logTextEdit->setPlainText(logHistory);
    lastResultLabel->setText(lastResultHistory);
    if (filenameLabel->text() != "") {
        calc->myCurResult = lastResultHistory.toDouble();
    }
}

void MainWindow::showCalculator(bool isChecked) {
    calc->setVisible(isChecked);
}
