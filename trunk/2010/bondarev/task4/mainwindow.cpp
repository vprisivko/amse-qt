#include <QTextStream>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent) {

    lastResult = 0;
    fileName = "";

    makeStatusBar();
    makeMenu();
    makeCentralWidget();
    makeCalcWidget();
    connections();
}

MainWindow::~MainWindow() {
    delete lFileName;
    delete lLastResult;
}

void MainWindow::makeStatusBar() {
    lFileName = new QLabel("File name:");
    lLastResult = new QLabel("0");
    lastResult = 0;
    this->statusBar()->addWidget(lFileName, 1);
    this->statusBar()->addWidget(lLastResult, 1);
}

void MainWindow::makeMenu() {
    open = new QAction("&Open", this);
    save = new QAction("&Save", this);
    revert = new QAction("&Revert", this);
    close = new QAction("&Close", this);
    calculator = new QAction("&Calculator", this);
    fileMenu = new QMenu("&File", this);
    fileMenu->addAction(open);
    fileMenu->addAction(save);
    fileMenu->addAction(revert);
    fileMenu->addAction(close);

    myMenu = new QMenuBar();
    myMenu->addMenu(fileMenu);
    myMenu->addAction(calculator);
    this->setMenuBar(myMenu);
}

void MainWindow::makeCentralWidget() {
    textEdit = new QTextEdit();
    textEdit->setReadOnly(true);
    this->setCentralWidget(textEdit);
}

void MainWindow::makeCalcWidget() {
    calcDialog = new QDialog(this);

    bnPlus = new QPushButton("+", calcDialog);
    bnMinus = new QPushButton("-", calcDialog);
    bnTimes = new QPushButton("*", calcDialog);
    bnDivide = new QPushButton("/", calcDialog);
    hLay = new QHBoxLayout();
    hLay->addWidget(bnPlus);
    hLay->addWidget(bnMinus);
    hLay->addWidget(bnTimes);
    hLay->addWidget(bnDivide);

    vLay = new QVBoxLayout(calcDialog);
    edit = new QLineEdit();
    vLay->addWidget(edit);
    vLay->addItem(hLay);
}

void MainWindow::connections() {
    connect(open, SIGNAL(triggered()), this, SLOT(sopen()));
    connect(save, SIGNAL(triggered()), this, SLOT(ssave()));
    connect(revert, SIGNAL(triggered()), this, SLOT(srevert()));
    connect(close, SIGNAL(triggered()), this, SLOT(sclose()));
    connect(calculator, SIGNAL(triggered()), this, SLOT(scalculator()));

    connect(bnPlus, SIGNAL(pressed()), this, SLOT(plus()));
    connect(bnMinus, SIGNAL(pressed()), this, SLOT(minus()));
    connect(bnTimes, SIGNAL(pressed()), this, SLOT(times()));
    connect(bnDivide, SIGNAL(pressed()), this, SLOT(divide()));
}

void MainWindow::sclose() {
    this->destroy(true, true);
}

void MainWindow::scalculator() {
    edit->setText(QString::number(lastResult));
    calcDialog->show();
}

void MainWindow::plus() {
    double first = lastResult,
        second = edit->text().toDouble();
    lastResult = first + second;
    textEdit->append(QString::number(first) + "+" + QString::number(second) + "=" + QString::number(lastResult));
}

void MainWindow::minus() {
    double first = lastResult,
        second = edit->text().toDouble();
    lastResult = first - second;
    textEdit->append(QString::number(first) + "-" + QString::number(second) + "=" + QString::number(lastResult));
}

void MainWindow::times() {
    double first = lastResult,
        second = edit->text().toDouble();
    lastResult = first * second;
    textEdit->append(QString::number(first) + "*" + QString::number(second) + "=" + QString::number(lastResult));
}

void MainWindow::divide() {
    double first = lastResult,
        second = edit->text().toDouble();
    lastResult = first / second;
    textEdit->append(QString::number(first) + "/" + QString::number(second) + "=" + QString::number(lastResult));
}

void MainWindow::sopen() {
    fileName = QFileDialog::getOpenFileName(this, "Open file", ".");
    if (QFile::exists(fileName)) {
        QFile file(fileName);

        if (file.open(QIODevice::ReadOnly)) {
            lFileName->setText("File name: " + fileName.section('/',-1));
            lastResult = QString(file.readLine()).toDouble();
            lLastResult->setText(QString::number(lastResult));
            edit->setText(QString::number(lastResult));
            textEdit->setText(QString(file.readAll()));
            file.close();
        }

    }

}

void MainWindow::ssave() {
    if(fileName.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this,"Save file");
    } else {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream toFile(&file);
            toFile << QString::number(lastResult) << "\n" << textEdit->toPlainText();
            lFileName->setText("File Name: " + fileName.section('/',-1));
            file.close();
        }
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
                textEdit->setText(QString(file.readAll()));
                file.close();
            }
        }
    }
}
