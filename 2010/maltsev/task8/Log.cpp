#include "Log.h"
#include <QMenuBar>
#include <QFile>
#include <QFileDialog>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QStatusBar>
#include <QSettings>

Log::Log(QWidget *parent): QMainWindow(parent) {
  opened = false;
  fileName = "";
  MW.setupUi(this);
  logName = new QLabel("Unsaved File", this);
  result = 0;
  lastResult = new QLabel("0", this);
  c = new Calculator(&result, MW.textEdit, lastResult, this);
  MW.statusbar->addWidget(logName);
  MW.statusbar->addPermanentWidget(lastResult);

  MW.menubar->addAction(MW.action_Open);
  MW.menubar->addAction(MW.action_Save);
  MW.menubar->addAction(MW.action_Revert);
  MW.menubar->addAction(MW.action_Calculator);
  connect(MW.action_Open, SIGNAL(triggered()),
          this, SLOT(Open()));
  connect(MW.action_Save, SIGNAL(triggered()),
          this, SLOT(Save()));
  connect(MW.action_Calculator, SIGNAL(triggered()),
          this, SLOT(Calc()));
  connect(MW.action_Revert, SIGNAL(triggered()),
          this, SLOT(Revert()));

  QSettings settings("asdfg", "log");

  settings.beginGroup("Log");
  resize(settings.value("size", QSize(400, 400)).toSize());
  move(settings.value("pos", QPoint(200, 200)).toPoint());
  settings.endGroup();

}

Log::~Log() {
  QSettings settings("asdfg", "log");

  settings.beginGroup("Log");
  settings.setValue("size", size());
  settings.setValue("pos", pos());
  settings.endGroup();

}

void Log::Open() {
  QString fileName1 = QFileDialog::getOpenFileName(this);
  if (fileName1 == "") return;
  QFile f(fileName1);
  if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) return;
  const char * p = (const char*)(f.map(0, f.size()));
  int i = 0;
  QString data;
  while (p[i] != '\n') {
    data += p[i];
    ++i;
  }
  lastResult->setText(data);
  result = data.toDouble();
  logName->setText(fileName1);
  MW.textEdit->setText(QString(p + i + 1));
  opened = true;
  fileName = fileName1;
  c->Reload(&result);
}

void Log::Save() {
  QString fileName1 = fileName;
  if (fileName1 == "") {
    fileName1 = QFileDialog::getSaveFileName(this);
    if (fileName1 == "") return;
  }
  QFile f(fileName1);
  if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) return;
  f.write(QByteArray((lastResult->text() + "\n").toAscii()).data());
  f.write(QByteArray(MW.textEdit->toPlainText().toAscii()).data());
  opened = true;
  fileName = fileName1;
  logName->setText(fileName);
  f.close();
}

void Log::Revert() {
  if (fileName == "") return;
  QFile f(fileName);
  if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) return;
  const char * p = (const char*)(f.map(0, f.size()));
  int i = 0;
  QString data;
  while (p[i] != '\n') {
    data += p[i];
    ++i;
  }
  lastResult->setText(data);
  result = data.toInt();
  MW.textEdit->setText(QString(p + i + 1));
  opened = true;
  c->Reload(&result);
}

void Log::Calc() {
  c->setVisible(!c->isVisible());
}
