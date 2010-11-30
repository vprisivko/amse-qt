#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include "LogWindow.h"
#include "ui_LogWindow.h"

LogWindow::LogWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::LogWindow) {
    ui->setupUi(this);
    filenameLabel = new QLabel("Unsaved file", this);
    resultLabel = new QLabel("0", this);
    calculator = new CalculatorDialog(this);
    filename = "";
    ui->statusBar->addWidget(filenameLabel);
    ui->statusBar->addWidget(resultLabel);
    connect(ui->actionOpen_file, SIGNAL(triggered()), this, SLOT(fileOpen()));
    connect(ui->actionSave_file, SIGNAL(triggered()), this, SLOT(fileSave()));
    connect(ui->actionRevert, SIGNAL(triggered()), this, SLOT(revert()));
    connect(ui->actionRun_calculator, SIGNAL(triggered()), this, SLOT(runCalculator()));
    connect(calculator, SIGNAL(addOperation(const QString &)), ui->logText, SLOT(append(const QString &)));
    connect(calculator, SIGNAL(resultChanged(double)), this, SLOT(updateResult(double)));
}

LogWindow::~LogWindow() {
    delete ui;
}

void LogWindow::runCalculator() {
        calculator->show();
}

void LogWindow::readFile() {
        if (!QFile::exists(filename)) {
                return;
        }
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                return;
        }
        QTextStream stream(&file);
        lastResult = stream.readLine().toDouble();
        while (!stream.atEnd()) {
                QString line = stream.readLine();
                ui->logText->append(line);
        }
        file.close();
}

void LogWindow::fileOpen() {
        filename = QFileDialog::getOpenFileName(this, "Open log file");
        readFile();
        calculator->setResult(lastResult);
        filenameLabel->setText(filename);
}

void LogWindow::fileSave() {
        if (filename == "") {
                filename = QFileDialog::getSaveFileName(this, "Save log file");
                filenameLabel->setText(filename);
        }
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                return;
        }
        QTextStream stream(&file);
        stream << lastResult << "\n" << ui->logText->toPlainText();
        file.close();
}

void LogWindow::revert() {
        ui->logText->clear();
        if (filename == "") {
                lastResult = 0;
        } else {
                readFile();
        }
        calculator->setResult(lastResult);
}

void LogWindow::updateResult(double result) {
        lastResult = result;
        resultLabel->setNum(result);
}
