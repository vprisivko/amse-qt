// =====================================================================================
// 
//       Filename:  mainwindow.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  14.10.2010 12:19:35
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#include "mainwindow.h"

#include <QMenuBar>
#include <QStatusBar>
#include <QBoxLayout>
#include <QSplitter>
#include <QDoubleValidator>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QFrame>
#include <QSettings>
#include <QToolBar>

MainWindow::MainWindow(QWidget *p) : QMainWindow(p), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    createStatusBar();
    createCalc();
    createConnections();
    createToolBar();

    lastResult = 0;
    previousResult = "0";
    previousLog = "";
    
    readSettings();
}

void MainWindow::closeEvent(QCloseEvent *) {
    writeSettings();
}

void MainWindow::writeSettings() {
    QSettings settings("Serdyuk Dmitriy", "task4");

    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.setValue("maximized", isMaximized());
    settings.endGroup();
}

void MainWindow::readSettings() {
    QSettings settings("Serdyuk Dmitriy", "task4");

    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    if (settings.value("maximized", false).toBool()) {
        setWindowState(Qt::WindowMaximized);
    }
    settings.endGroup();
}

void MainWindow::createToolBar() {
    ui->actionToggle_calculator->setIcon(QIcon("calc.svg"));
    ui->toolBar->addAction(ui->actionToggle_calculator);
}

void MainWindow::createStatusBar() {
    QWidget *widget = new QWidget(ui->statusbar);
    ui->statusbar->addWidget(widget);
    QHBoxLayout *statusLayout = new QHBoxLayout;
    widget->setLayout(statusLayout);
    myLogName = new QLabel(widget);
    myOperationResult = new QLabel(widget);
    statusLayout->addWidget(myLogName);
    
    QFrame *frame = new QFrame(widget);
    frame->setFrameStyle(QFrame::VLine | QFrame::Raised);
    statusLayout->addWidget(frame);

    statusLayout->addWidget(myOperationResult);
}

void MainWindow::createCalc() {
    myCalculator = new QWidget;
    myCalculator->hide();
    
    QVBoxLayout *layout = new QVBoxLayout;
    myCalculator->setLayout(layout);

    myCalcEdit = new QLineEdit(myCalculator);
    myCalcEdit->setValidator(new QDoubleValidator(myCalcEdit));
    myCalcEdit->setText("0");
    layout->addWidget(myCalcEdit);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    layout->addLayout(buttonLayout);

    myPlusButton = new QPushButton("+", myCalculator);
    mySubsButton = new QPushButton("-", myCalculator);
    myMultButton = new QPushButton("*", myCalculator);
    myDivButton = new QPushButton("/", myCalculator);

    buttonLayout->addWidget(myPlusButton);
    buttonLayout->addWidget(mySubsButton);
    buttonLayout->addWidget(myMultButton);
    buttonLayout->addWidget(myDivButton);

}

void MainWindow::createConnections() {
    connect(myPlusButton, SIGNAL(clicked()), this, SLOT(add()));
    connect(mySubsButton, SIGNAL(clicked()), this, SLOT(substrate()));
    connect(myMultButton, SIGNAL(clicked()), this, SLOT(multiply()));
    connect(myDivButton, SIGNAL(clicked()), this, SLOT(divide()));
}

void MainWindow::add() {
    changeLastResult('+');
}

void MainWindow::substrate() {
    changeLastResult('-');
}

void MainWindow::multiply() {
    changeLastResult('*');
}

void MainWindow::divide() {
    changeLastResult('/');
}

void MainWindow::changeLastResult(char operation) {
    double a = lastResult;
    double b = myCalcEdit->text().toDouble();
    if (operation == '+') {
        lastResult += b;
    } else if (operation == '-') {
        lastResult -= b;
    } else if (operation == '*') {
        lastResult *= b;
    } else if (operation == '/') {
        lastResult /= b;
    }
    myOperationResult->setText(QString("Last operation result: %1").arg(lastResult));
    myCalcEdit->setText(QString("%1").arg(lastResult));

    ui->textEdit->insertPlainText(QString("%1 %2 %3 = %4\n").arg(a).arg(operation).arg(b).arg(lastResult));
}

void MainWindow::on_action_Open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Log", "./", "Log File (*.log);;All Files (*)");
    if (fileName == "") {
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }


    QTextStream in(&file);
    QString s;
    in >> lastResult;

    myOperationResult->setText(QString("Last operation result: %1").arg(lastResult));
    myCalcEdit->setText(QString("%1").arg(lastResult));

    in.readLine();
    for (;!in.atEnd();) {
        s += in.readLine() + "\n";
    }
    ui->textEdit->setPlainText("");
    ui->textEdit->insertPlainText(s);
    previousLog = s;
    previousResult = QString("%1").arg(lastResult);
    file.close();

    QStringList l = fileName.split("/");
    myLogName->setText("File: " + l[l.size() - 1]);
}

void MainWindow::on_action_Save_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Log", "./", "Log File (*.log)");
    if (!fileName.endsWith(".log", Qt::CaseInsensitive)) {
        fileName += ".log";
    }
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << lastResult << "\n";
    out << ui->textEdit->toPlainText();
    file.close();
}

void MainWindow::on_action_Revert_triggered()
{
    ui->textEdit->setPlainText("");
    ui->textEdit->insertPlainText(previousLog);
    myOperationResult->setText(QString("Last operation result: %1").arg(previousResult));
    myCalcEdit->setText(previousResult);
}

void MainWindow::on_actionToggle_calculator_triggered()
{
    if (myCalculator->isVisible()) {
        myCalculator->hide();
    } else {
        myCalculator->show();
    }
}
