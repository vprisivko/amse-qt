#include "Calculator.h"
#include "QMenuBar"
#include "QStatusBar"
#include "QMenu"
#include "QDebug"
#include "QVBoxLayout"
#include "QPushButton"
#include "QHBoxLayout"
#include "QFile"
#include "QFileDialog"
#include "QMessageBox"
#include "QScrollArea"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
{
    this->setMinimumSize(500, 500);

    createMenu();
    createCalculator();
    createLogWidget();
    createStatusBar();

    lastValue = 0;
    fileName = "";
}

void Calculator::createMenu() {
    QMenu *optMenu = new QMenu("Options", this);
    menuBar()->addMenu(optMenu);
    menuBar()->addAction("Calculator", this, SLOT(calcPressed()));

    optMenu->addAction("Open", this, SLOT(openFile(bool)));
    optMenu->addAction("Save", this, SLOT(saveFile()));
    optMenu->addAction("Revert", this, SLOT(revertFile()));
}

void Calculator::createCalculator() {
    calcDialog = new QDialog(this);
    calcDialog->setLayout(new QVBoxLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    lineEdit = new QLineEdit("0", calcDialog);
    calcDialog->layout()->addWidget(lineEdit);

    QPushButton *addButton = new QPushButton("+", calcDialog);
    addButton->setObjectName("+");
    QPushButton *subButton = new QPushButton("-", calcDialog);
    subButton->setObjectName("-");
    QPushButton *multiplyButton = new QPushButton("*", calcDialog);
    multiplyButton->setObjectName("*");
    QPushButton *divideButton = new QPushButton("/", calcDialog);
    divideButton->setObjectName("/");
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(subButton);
    buttonLayout->addWidget(multiplyButton);
    buttonLayout->addWidget(divideButton);

    calcDialog->layout()->addItem(buttonLayout);

    connect(addButton, SIGNAL(pressed()), this, SLOT(calcButtonPressed()));
    connect(subButton, SIGNAL(pressed()), this, SLOT(calcButtonPressed()));
    connect(multiplyButton, SIGNAL(pressed()), this, SLOT(calcButtonPressed()));
    connect(divideButton, SIGNAL(pressed()), this, SLOT(calcButtonPressed()));
}

void Calculator::createLogWidget() {
    centralLabel = new QLabel();
    QScrollArea* scrollArea = new QScrollArea(this);
    setCentralWidget(scrollArea);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(centralLabel);
}

void Calculator::createStatusBar() {
    resultLabel = new QLabel("0");
    statusBar()->addWidget(resultLabel);
    fileNameLabel = new QLabel("no file selected");
    statusBar()->addWidget(fileNameLabel);
}

void Calculator::openFile(bool revert) {
    //Is file opened or reverted
    if (!revert) {
        QFileDialog *fileDialog = new QFileDialog(this, "Select File");
        fileName = fileDialog->getOpenFileName();
    }

    QFile *file = new QFile(fileName);
    file->open(QIODevice::ReadOnly);

    //Last Value
    QString result = file->readLine();
    lastValue = result.toDouble();

    //Log
    fileContent = file->readAll();

    centralLabel->setText(fileContent);

    file->close();

    if (revert) {
        QMessageBox *fileClosed = new QMessageBox(this);
        fileClosed->information(this, "Information", "File reverted");
    }

    fileNameLabel->setText(fileName);
    resultLabel->setText(QString().number(lastValue));
}

void Calculator::saveFile() {
    if (fileName.isEmpty()) {
        fileName = QFileDialog( this, "Select file" ).getSaveFileName();
    }

    QFile *file = new QFile(fileName);
    file->open(QIODevice::WriteOnly);

    file->write(QString().number(lastValue).toAscii());

    file->write("\n");
    file->write(fileContent.toAscii());

    file->close();

    QMessageBox *fileClosed = new QMessageBox(this);
    fileClosed->information(this, "Information", "File saved");
}

void Calculator::revertFile() {
    if (fileName.isEmpty()) {
        QMessageBox *error = new QMessageBox(this);
        error->warning(this, "Error", "No selected file");
        return;
    }
    emit openFile(true);
}

void Calculator::calcPressed() {
    calcDialog->setVisible(calcDialog->isHidden());
}


void Calculator::calcButtonPressed() {
   QString objectName = sender()->objectName();

   //Divide on "0"
   if ((lineEdit->text().toDouble() == 0) && (objectName.compare("/") == 0)) {
       QMessageBox *error = new QMessageBox(this);
       error->warning(this, "Error", "Action is impossible");
       return;
   }

   fileContent += QString().number(lastValue) + " " + objectName + " " + lineEdit->text() + " = ";
    if (objectName.compare("+") == 0) {
        lastValue += lineEdit->text().toDouble();
    } else if (objectName.compare("-") == 0) {
        lastValue -= lineEdit->text().toDouble();
    } else if (objectName.compare("*") == 0) {
        lastValue *= lineEdit->text().toDouble();
    } else if (objectName.compare("/") == 0) {
        lastValue /= lineEdit->text().toDouble();
    }

    fileContent += QString().number(lastValue) + "\n";
    centralLabel->setText(fileContent);

    resultLabel->setText(QString().number(lastValue));
    lineEdit->setText("0");

    if(QString().number(lastValue) == "nan") {
        lastValue = 0;
    }
}
