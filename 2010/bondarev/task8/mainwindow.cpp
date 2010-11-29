#include <QFileDialog>
#include <QFile>
#include <QTextStream>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->centralWidget->setLayout(ui->textLayout);

    fileName = "";

    makeStatusBar();
    makeMenu();
    makeCalcWidget();
    connections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makeStatusBar() {
    lFileName = new QLabel("File name:");
    lLastResult = new QLabel("0");
    lastResultIsExist = false;
    lastResult = 0;
    ui->statusBar->addWidget(lFileName, 1);
    ui->statusBar->addWidget(lLastResult, 1);
}

void MainWindow::makeCalcWidget() {
    calcDialog = new QDialog(this);

    bnPlus = new QPushButton("+", calcDialog);
    bnMinus = new QPushButton("-", calcDialog);
    bnTimes = new QPushButton("*", calcDialog);
    bnDivide = new QPushButton("/", calcDialog);
    QHBoxLayout *hLay = new QHBoxLayout();
    hLay->addWidget(bnPlus);
    hLay->addWidget(bnMinus);
    hLay->addWidget(bnTimes);
    hLay->addWidget(bnDivide);

    QVBoxLayout *vLay = new QVBoxLayout(calcDialog);
    edit = new QLineEdit();
    vLay->addWidget(edit);
    vLay->addItem(hLay);
}

void MainWindow::makeMenu() {
    calculator = new QAction("&Calculator", this);
    ui->menuBar->addAction(calculator);
}

void MainWindow::connections() {
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(sopen()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(ssave()));
    connect(ui->actionRevert, SIGNAL(triggered()), this, SLOT(srevert()));
    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(sclose()));
    connect(calculator, SIGNAL(triggered()), this, SLOT(scalculator()));

    connect(bnPlus, SIGNAL(pressed()), this, SLOT(plus()));
    connect(bnMinus, SIGNAL(pressed()), this, SLOT(minus()));
    connect(bnTimes, SIGNAL(pressed()), this, SLOT(times()));
    connect(bnDivide, SIGNAL(pressed()), this, SLOT(divide()));
}
void MainWindow::plus() {
    double first = lastResult,
    second = edit->text().toDouble();
    if (lastResultIsExist) {
        lastResult = first + second;
        ui->textEdit->append(QString::number(first) + "+" + QString::number(second) + "=" + QString::number(lastResult));
    } else {
        lastResult = second;
        lastResultIsExist = true;
    }
    lLastResult->setText(QString::number(lastResult));
}

void MainWindow::minus() {
    double first = lastResult,
    second = edit->text().toDouble();
    if (lastResultIsExist) {
        lastResult = first - second;
        ui->textEdit->append(QString::number(first) + "-" + QString::number(second) + "=" + QString::number(lastResult));
    } else {
        lastResult = second;
        lastResultIsExist = true;
    }
    lLastResult->setText(QString::number(lastResult));
}

void MainWindow::times() {
    double first = lastResult,
    second = edit->text().toDouble();
    if (lastResultIsExist) {
        lastResult = first * second;
        ui->textEdit->append(QString::number(first) + "*" + QString::number(second) + "=" + QString::number(lastResult));
    } else {
        lastResult = second;
        lastResultIsExist = true;
    }
    lLastResult->setText(QString::number(lastResult));
}

void MainWindow::divide() {
    double first = lastResult,
    second = edit->text().toDouble();
    if (lastResultIsExist) {
        if (second != 0) {
            lastResult = first / second;
            ui->textEdit->append(QString::number(first) + "/" + QString::number(second) + "=" + QString::number(lastResult));
        }
    } else {
        lastResult = second;
        lastResultIsExist = true;
    }
    lLastResult->setText(QString::number(lastResult));
}

void MainWindow::sopen() {
    fileName = QFileDialog::getOpenFileName(this, "Open file", ".");
    if (QFile::exists(fileName)) {
        QFile file(fileName);

        if (file.open(QIODevice::ReadOnly)) {
            lFileName->setText("File name: " + fileName.section('/',-1));
            lastResult = QString(file.readLine()).toDouble();
            lastResultIsExist = true;
            lLastResult->setText(QString::number(lastResult));
            edit->setText(QString::number(lastResult));
            ui->textEdit->setText(QString(file.readAll()));
            file.close();
        }
    }
}

void MainWindow::ssave() {
    if(fileName.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this,"Save file");
        lFileName->setText("FileName: " + fileName.section('/',-1));
    }
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream toFile(&file);
        toFile << QString::number(lastResult) << "\n" << ui->textEdit->toPlainText();
        lFileName->setText("File Name: " + fileName.section('/',-1));
        file.close();
    }

}

void MainWindow::srevert() {
    if(!fileName.isEmpty()) {
        if(QFile::exists(fileName)) {
            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly)) {
                lastResult = QString(file.readLine()).toDouble();
                lLastResult->setText(QString::number(lastResult));
                edit->setText(QString::number(lastResult));
                ui->textEdit->setText(QString(file.readAll()));
                file.close();
            }
        }
    }
}

void MainWindow::sclose() {
    this->destroy(true, true);
}

void MainWindow::scalculator() {
    edit->setText(QString::number(lastResult));
    calcDialog->show();
}

