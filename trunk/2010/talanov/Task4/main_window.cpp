#include "main_window.h"

#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>

#include <QtGui/QFileDialog>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QTextDocument>

CalculatorLogMW::CalculatorLogMW(QWidget *parent, Qt::WFlags flags)
: QMainWindow(parent, flags) ,myFilename("")
{
  
  setUpWidgets();
  createActions();
  setUpMenu();
  connectToSlots();

  setResult(0);
}

CalculatorLogMW::~CalculatorLogMW()
{

}

void CalculatorLogMW::setUpWidgets()
{
  setUpStatusBar();
  myTextEdit = new QPlainTextEdit(this);
  setCentralWidget(myTextEdit);
  myTextEdit->setReadOnly(true);
  myCalculator = new Calculator(this);
}

void CalculatorLogMW::setUpStatusBar()
{
  myStatusLogFilenameLabel = new QLabel(statusBar());
  myStatusResultLabel = new QLabel(statusBar());
  statusBar()->addWidget(myStatusLogFilenameLabel, 1);
  statusBar()->addWidget(myStatusResultLabel);
  myStatusLogFilenameLabel->setText("untitled");
}

void CalculatorLogMW::createActions()
{
  myOpenAction = new QAction("Open...", this);
  mySaveAction = new QAction("Save", this);
  mySaveAsAction = new QAction("Save as...", this);
  myRevertAction = new QAction("Revert", this);
  myCalculatorAction =  new QAction("Calculator", this);
}

void CalculatorLogMW::setUpMenu()
{
  QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(myOpenAction);
  fileMenu->addAction(mySaveAction);
  fileMenu->addAction(mySaveAsAction);
  fileMenu->addAction(myRevertAction);
  menuBar()->addAction(myCalculatorAction);
}

void CalculatorLogMW::connectToSlots()
{
  connect(myOpenAction, SIGNAL(triggered()), this, SLOT(openFile()));
  connect(mySaveAction, SIGNAL(triggered()), this, SLOT(saveFile()));
  connect(mySaveAsAction, SIGNAL(triggered()), this, SLOT(saveFileAs()));
  connect(myRevertAction, SIGNAL(triggered()), this, SLOT(revertFile()));
  connect(myCalculatorAction, SIGNAL(triggered()), this, SLOT(calculator()));

  connect(myCalculator, SIGNAL(addText(const QString&)), this, SLOT(addText(const QString&)));
  connect(myCalculator, SIGNAL(resultChanged(int)), this, SLOT(setResult(int)));
}

void CalculatorLogMW::openFile()
{
  QString newFilename = QFileDialog::getOpenFileName(this, "Select file to open", "", "Log files (*.log)");
  if (newFilename == QString())
  {
    return;
  }
  openFile(newFilename);
}

void CalculatorLogMW::openFile(const QString& filename)
{
  setFilename(filename);

  QFile file(myFilename);
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QTextStream stream(&file);

  //retrieve last Value
  QString result = file.readLine();
  setResult(result.toInt());

  myTextEdit->setPlainText(stream.readAll());
}

void CalculatorLogMW::setResult(int res)
{
  myResult = res;
  if (myResult != myCalculator->result())
  {
    myCalculator->setResult(myResult);
  }
  myStatusResultLabel->setText(QString::number(res));
}

void CalculatorLogMW::saveFile()
{
  if (myFilename == QString())
  {
    saveFileAs();
  }

  QFile file(myFilename);
  file.open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream stream(&file);

  //write last value
  stream << QString::number(myResult) << '\n';
  stream << myTextEdit->toPlainText();
}

void CalculatorLogMW::saveFileAs()
{
  QString saveFilename = QFileDialog::getSaveFileName(this, "Select file to save", "", "Log files (*.log)");
  if (saveFilename == QString())
  {
    return;
  }

  setFilename(saveFilename);
  saveFile();
}

void CalculatorLogMW::calculator()
{
  myCalculator->setVisible(!myCalculator->isVisible());
}

void CalculatorLogMW::revertFile()
{
  openFile(myFilename);
}

void CalculatorLogMW::addText(const QString& text)
{
  myTextEdit->appendPlainText(text);
}

void CalculatorLogMW::setFilename(const QString& name)
{
  myFilename = name;
  myStatusLogFilenameLabel->setText(name);
}