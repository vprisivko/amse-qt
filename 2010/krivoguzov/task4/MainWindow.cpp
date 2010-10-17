#include "MainWindow.h"
#include <QtGui>
#include <QDockWidget>

MainWindow::MainWindow(){
    createActions();
    createMenu();
    createMainArea();
    createToolBar();
    createStatusBar();
    createDockCalculator();

    myResult=0;
}

void MainWindow::createActions()
{
    newAction = new QAction(QIcon(":/images/filenew.png"), "&New", this);
    newAction->setShortcuts(QKeySequence::New);
    newAction->setStatusTip("Create a new file");
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

    openAction = new QAction(QIcon(":/images/fileopen.png"), "&Open...", this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip("Open an existing file");
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(QIcon(":/images/filesave.png"), "&Save", this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip("Save the document to disk");
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAction = new QAction(QIcon(":/images/filesaveas.png"), "Save &As...", this);
    saveAsAction->setShortcuts(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    revertAction = new QAction(QIcon(":/images/revert.png"),"Revert",this);
    revertAction->setStatusTip("Revert the changes");
    connect(revertAction, SIGNAL(triggered()), this, SLOT(revert()));

    exitAction = new QAction("E&xit", this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip("Exit the application");
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::createMenu(){

    myMenu = menuBar()->addMenu("&File");
    myViewMenu = menuBar()->addMenu("&View");
    myMenu->addAction(newAction);
    myMenu->addAction(openAction);
    myMenu->addAction(saveAction);
    myMenu->addAction(saveAsAction);
    myMenu->addAction(revertAction);
    myMenu->addSeparator();
    myMenu->addAction(exitAction);

}

void MainWindow::createToolBar(){

    QToolBar *myToolBar = addToolBar("File");
    myToolBar->addAction(newAction);
    myToolBar->addAction(openAction);
    myToolBar->addAction(saveAction);
    myToolBar->addAction(saveAsAction);
    myToolBar->addAction(revertAction);

}

void MainWindow::createMainArea(){

    setGeometry(100,100,900,600);
    myTextEdit = new QPlainTextEdit(this);
    myTextEdit->setReadOnly(true);
    setCentralWidget(myTextEdit);
    setWindowTitle("Logger");

}

void MainWindow::createStatusBar(){

    logNameLabel = new QLabel("Log name:");
    logName= new QLabel("untitled.log");
    lastResultLabel = new QLabel("Last result:");
    lastResult = new QLabel("0");
    statusBar()->addWidget(logNameLabel);
    statusBar()->addWidget(logName);
    statusBar()->addWidget(lastResultLabel);
    statusBar()->addWidget(lastResult);

    connect(myTextEdit,SIGNAL(textChanged()),this,SLOT(documentWasModified()));
}

void MainWindow::createDockCalculator()
{

    plusButton = new QPushButton("+");
    minusButton = new QPushButton("-");
    multButton = new QPushButton("*");
    divideButton = new QPushButton("/");

    connect(plusButton ,SIGNAL(clicked()),this,SLOT(plusPressed()));
    connect(minusButton,SIGNAL(clicked()),this,SLOT(minusPressed()));
    connect(multButton,SIGNAL(clicked()),this,SLOT(multPressed()));
    connect(divideButton,SIGNAL(clicked()),this,SLOT(dividePressed()));

    myInput = new QLineEdit();
    myInput->setAlignment(Qt::AlignRight);

    QHBoxLayout *hlay = new QHBoxLayout();
    hlay->addWidget(plusButton);
    hlay->addWidget(minusButton);
    hlay->addWidget(multButton);
    hlay->addWidget(divideButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(myInput);
    mainLayout->addLayout(hlay);

    myCalculator = new QDialog();
    myCalculator->setLayout(mainLayout);
    myCalculator->setMaximumHeight(myCalculator->sizeHint().height());
    myCalculator->setMaximumWidth(myCalculator->sizeHint().width());

    QDockWidget *dock = new QDockWidget("Calculator", this);
    dock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    dock->setWidget(myCalculator);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    myViewMenu->addAction(dock->toggleViewAction());

}

void MainWindow::plusPressed(){

    int b = QString(myInput->text()).toInt();
    QString newCalc = QString::number(myResult).append(" + ").append(QString::number(b)).append(" = ")
            .append(QString::number(myResult + b));
    myResult += b;
    myTextEdit->appendPlainText(newCalc);

}

void MainWindow::minusPressed(){

    int b = QString(myInput->text()).toInt();
    QString newCalc = QString::number(myResult).append(" - ").append(QString::number(b)).append(" = ")
            .append(QString::number(myResult - b));
    myResult -= b;
    myTextEdit->appendPlainText(newCalc);

}

void MainWindow::multPressed(){

    int b = QString(myInput->text()).toInt();
    QString newCalc = QString::number(myResult).append(" * ").append(QString::number(b)).append(" = ")
            .append(QString::number(myResult * b));
    myResult *= b;
    myTextEdit->appendPlainText(newCalc);

}

void MainWindow::dividePressed(){

    int b = QString(myInput->text()).toInt();
    QString newCalc = QString::number(myResult).append(" / ").append(QString::number(b)).append(" = ")
            .append(QString::number(myResult / b));
    myResult /= b;
    myTextEdit->appendPlainText(newCalc);

}

void MainWindow::documentWasModified(){

    lastResult->setText(QString::number(myResult));

}

void MainWindow::newFile(){

    curFile = "";
    myTextEdit->setPlainText("");
    myResult = 0;
    logName->setText("untitled.log");
    lastResult->setText(QString::number(myResult));

}


void MainWindow::revert(){

    loadFile(curFile);

}

bool MainWindow::save(){

    if (curFile.isEmpty())
        return saveAs();
    else
        return saveFile(curFile);

}

bool MainWindow::saveAs(){

    QString fileName = QFileDialog::getSaveFileName(this, "Save log");
    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);

}

void MainWindow::open(){

    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadFile(fileName);

}

bool MainWindow::saveFile(const QString &fileName){

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Logger", "Cannot write file!");
        return false;
    }
    QTextStream out(&file);
    out << myResult << "\n";
    out << myTextEdit->toPlainText();
    curFile = fileName;
    logName->setText(curFile);
    return true;

 }

void MainWindow::loadFile(const QString &fileName){

     QFile file(fileName);
     if (!file.open(QFile::ReadOnly | QFile::Text)) {
         QMessageBox::warning(this, "Logger", "Cannot read file!");
         return;
     }

     QTextStream in(&file);
     myResult = in.readLine().toInt();
     lastResult->setText(QString::number(myResult));

     while(!in.atEnd())
        myTextEdit->setPlainText(in.readAll());

     curFile = fileName;
     logName->setText(fileName);

 }




