#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    logHistory(""),
    lastResultHistory("0")
{
    ui->setupUi(this);
    calc = new Calculator(this);
    filenameLabel = new QLabel("Unsaved file");
    lastResultLabel = new QLabel("0");
    statusBar()->addWidget(filenameLabel);
    statusBar()->addPermanentWidget(lastResultLabel);
    setCentralWidget(ui->logTextEdit);

    connect(ui->actionOpenFile, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    connect(ui->actionSaveFile, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    connect(ui->actionRevertFile, SIGNAL(triggered(bool)), this, SLOT(revertFile()));
    connect(ui->actionShowCalculator, SIGNAL(triggered(bool)), this, SLOT(showCalculator(bool)));
    connect(calc, SIGNAL(toWrite(QString, double)), this, SLOT(addToLog(QString, double)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addToLog(QString str, double res) {
    ui->logTextEdit->setPlainText(ui->logTextEdit->toPlainText() + str + "\n");
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
    ui->logTextEdit->setPlainText(logHistory);
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
    stream << ui->logTextEdit->toPlainText();
    logHistory = ui->logTextEdit->toPlainText();
    lastResultHistory = lastResultLabel->text();
    filenameLabel->setText(filename);
    file.close();
}

void MainWindow::revertFile() {
    ui->logTextEdit->setPlainText(logHistory);
    lastResultLabel->setText(lastResultHistory);
    if (filenameLabel->text() != "") {
        calc->myCurResult = lastResultHistory.toDouble();
    }
}

void MainWindow::showCalculator(bool isChecked) {
    calc->setVisible(isChecked);
}
