#include "calculatorlogmw.h"
#include "ui_calculatorlogmw.h"

#include <QtGui/QFileDialog>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QTextDocument>


CalculatorLogMW::CalculatorLogMW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CalculatorLogMW)
{
    ui->setupUi(this);
    setUpStatusBar();
    myCalculator = new Calculator(this);
    setFilename("untitled");
    connectToSlots();
    setResult(0.0f);
}

void CalculatorLogMW::setUpStatusBar()
{
  myStatusLogFilenameLabel = new QLabel(statusBar());
  myStatusResultLabel = new QLabel(statusBar());
  statusBar()->addWidget(myStatusLogFilenameLabel, 1);
  statusBar()->addWidget(myStatusResultLabel);
  myStatusLogFilenameLabel->setText("untitled");
}

CalculatorLogMW::~CalculatorLogMW()
{
    delete ui;
}


void CalculatorLogMW::connectToSlots()
{
//  connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
//  connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
//  connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(saveFileAs()));
//  connect(ui->actionRevert, SIGNAL(triggered()), this, SLOT(revertFile()));
//  connect(ui->actionCacluclator, SIGNAL(triggered()), this, SLOT(calculator()));

  connect(myCalculator, SIGNAL(addText(const QString&)), this, SLOT(addText(const QString&)));
  connect(myCalculator, SIGNAL(resultChanged(qreal)), this, SLOT(setResult(qreal)));
}

void CalculatorLogMW::openFile()
{
  QString newFilename = QFileDialog::getOpenFileName(this, "Select file to open", "", "Log files (*.log);;All files (*.*)");
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
  setResult(result.toDouble());

  ui->plainTextEdit->setPlainText(stream.readAll());
}

void CalculatorLogMW::setResult(qreal res)
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
  stream << ui->plainTextEdit->toPlainText();
}

void CalculatorLogMW::saveFileAs()
{
  QString saveFilename = QFileDialog::getSaveFileName(this, "Select file to save", myFilename + ".log", "All files (*.*)");
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
  ui->plainTextEdit->appendPlainText(text);
}

void CalculatorLogMW::setFilename(const QString& name)
{
  myFilename = name;
  myStatusLogFilenameLabel->setText(name);
}
