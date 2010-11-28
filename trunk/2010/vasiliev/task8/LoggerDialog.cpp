#include <QApplication>
#include <QFileDialog>
#include <QIODevice>
#include <QFile>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextStream>

#include "LoggerDialog.h"
#include "ui_LoggerDialog.h"

CalcLog::CalcLog(QWidget *parent): QMainWindow(parent) {

	setWindowTitle("Calculation Logger");

	MW.setupUi(this);

	myFileNameLabel = new QLabel("", this);
	myResultLabel = new QLabel("0", this);
	myCalcDialog = new CalcDialog(this);
	myCalcDialog->setVisible(false);

	statusBar()->addWidget(myFileNameLabel);
	statusBar()->addWidget(myResultLabel);
	setCentralWidget(MW.processEdit);
	
	QObject::connect(MW.actionOpen, SIGNAL(triggered(bool)), this, SLOT(openFile()));
	QObject::connect(MW.actionSave, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
	QObject::connect(MW.actionRevert, SIGNAL(triggered(bool)), this, SLOT(revertFile()));
	QObject::connect(MW.actionExit, SIGNAL(triggered(bool)), this, SLOT(exit()));
	QObject::connect(MW.actionCalculator, SIGNAL(triggered(bool)), this, SLOT(calc()));

	QObject::connect(myCalcDialog, SIGNAL(sendExpression(QString, int)),
			this, SLOT(recieveExpression(QString, int)));
}

void CalcLog::openFile() {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
						".",
						tr("Calculation Files (*.cf)"));
	if (QFile::exists(fileName)) {
		QFile file(fileName);
		if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			myFileNameLabel->setText(fileName);

			QTextStream stream(&file);
			myLogResult = stream.readLine();
			myResultLabel->setText(myLogResult);
			myLogHistory = "";
			while (!stream.atEnd()) {
				QString nextLine = stream.readLine();
				myLogHistory += nextLine + "\n";
			}
			file.close();

			MW.processEdit->setPlainText(myLogHistory);
			myCalcDialog->setResult(myLogResult.toInt());
		}
	}
}

void CalcLog::saveFile() {
	QString fileName;
	if (myFileNameLabel->text() == "") {
		fileName = QFileDialog::getSaveFileName(this, tr("Open File"),
							".",
							tr("Calculation files (*.cf)"));
		if (!fileName.endsWith(".cf")) {
			fileName += ".cf";
		}
	} else {
		fileName = myFileNameLabel->text();
	}

	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		return;
	}

	QTextStream stream(&file);
	stream << myResultLabel->text() << "\n";
	stream << MW.processEdit->toPlainText();
	myLogHistory = MW.processEdit->toPlainText();
	myLogResult = myResultLabel->text();
	myFileNameLabel->setText(fileName);

	file.close();

}

void CalcLog::revertFile() {
	MW.processEdit->setPlainText(myLogHistory);
	myResultLabel->setText(myLogResult);
	myCalcDialog->setResult(myLogResult.toInt());
}

void CalcLog::calc() {
	myCalcDialog->setVisible(!myCalcDialog->isVisible());
}

void CalcLog::exit() {
	qApp->quit();
}

void CalcLog::recieveExpression(QString expression, int result) {
	MW.processEdit->setPlainText(MW.processEdit->toPlainText() + expression + "\n");
	myResultLabel->setText(QString::number(result));
}
