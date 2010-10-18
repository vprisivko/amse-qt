#include <QApplication>
#include <QFileDialog>
#include <QIODevice>
#include <QFile>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextStream>

#include "LoggerDialog.h"

CalcLog::CalcLog(QWidget *parent): QMainWindow(parent) {

	setWindowTitle("Calculation Logger");

	myOpenFileAction = new QAction(tr("&Open"), this);
	mySaveFileAction = new QAction(tr("&Save"), this);
	myRevertFileAction = new QAction(tr("&Revert"), this);
	myCalcAction = new QAction(tr("Cal&culator"), this);
	myCalcAction->setCheckable(true);
	myExitAction = new QAction(tr("E&xit"), this);
	myFileNameLabel = new QLabel("", this);
	myResultLabel = new QLabel("0", this);
	myProcessEdit = new QTextEdit(this);
	myCalcDialog = new CalcDialog(this);
	myCalcDialog->setVisible(false);

	QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
	QMenu *calcMenu = menuBar()->addMenu(tr("&Calc"));

	fileMenu->addAction(myOpenFileAction);
	fileMenu->addAction(mySaveFileAction);
	fileMenu->addAction(myRevertFileAction);
	fileMenu->addAction(myExitAction);
	calcMenu->addAction(myCalcAction);
	statusBar()->addWidget(myFileNameLabel);
	statusBar()->addWidget(myResultLabel);
	setCentralWidget(myProcessEdit);
	
	QObject::connect(myOpenFileAction, SIGNAL(triggered(bool)), this, SLOT(openFile()));
	QObject::connect(mySaveFileAction, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
	QObject::connect(myRevertFileAction, SIGNAL(triggered(bool)), this, SLOT(revertFile()));
	QObject::connect(myExitAction, SIGNAL(triggered(bool)), this, SLOT(exit()));
	QObject::connect(myCalcAction, SIGNAL(triggered(bool)), this, SLOT(calc()));

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

			myProcessEdit->setPlainText(myLogHistory);
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
	} else {
		fileName = myFileNameLabel->text();
	}

	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		return;
	}

	QTextStream stream(&file);
	stream << myResultLabel->text() << "\n";
	stream << myProcessEdit->toPlainText();
	myLogHistory = myProcessEdit->toPlainText();
	myLogResult = myResultLabel->text();
	myFileNameLabel->setText(fileName);

	file.close();

}

void CalcLog::revertFile() {
	myProcessEdit->setPlainText(myLogHistory);
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
	myProcessEdit->setPlainText(myProcessEdit->toPlainText() + expression + "\n");
	myResultLabel->setText(QString::number(result));
}
