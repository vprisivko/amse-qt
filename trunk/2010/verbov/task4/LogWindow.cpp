#include <QMenuBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "LogWindow.h"

LogWindow::LogWindow(QWidget *parent) : QMainWindow(parent) {
	filenameLabel = new QLabel("Unsaved file", this);
	resultLabel = new QLabel("0", this);
	
	calculator = new CalculatorDialog(this);
	filename = "";
	
	setWindowTitle("Log of calculation");

	createActions();
	createMenu();
	createStatusBar();
	createCentralWidget();
	connectSignalsAndSlots();
}

void LogWindow::createActions() {
	openAction = new QAction("&Open file", this);
	saveAction = new QAction("&Save file", this);
	revertAction = new QAction("&Revert", this);
	calculatorAction = new QAction("Run &calculator", this);
}

void LogWindow::createMenu() {
	QMenu *menu = menuBar()->addMenu("File");
	menu->addAction(openAction);
	menu->addAction(saveAction);
	menu->addAction(revertAction);
	menu->addAction(calculatorAction);
}

void LogWindow::createStatusBar() {
	statusBar()->addWidget(filenameLabel, 1);
	statusBar()->addWidget(resultLabel, 1);
}

void LogWindow::createCentralWidget() {
	logText = new QTextEdit(this);
	logText->setReadOnly(true);
	setCentralWidget(logText);
}

void LogWindow::connectSignalsAndSlots() {
	connect(openAction, SIGNAL(triggered()), this, SLOT(fileOpen()));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(fileSave()));
	connect(revertAction, SIGNAL(triggered()), this, SLOT(revert()));
	connect(calculatorAction, SIGNAL(triggered()), this, SLOT(runCalculator()));
	connect(calculator, SIGNAL(addOperation(const QString &)), logText, SLOT(append(const QString &)));
	connect(calculator, SIGNAL(resultChanged(double)), this, SLOT(updateResult(double)));
}

void LogWindow::runCalculator() {
	calculator->show();
}

void LogWindow::readFile() {
	if (!QFile::exists(filename)) {
		return;
	}
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return;
	}
	QTextStream stream(&file);
	lastResult = stream.readLine().toDouble();
	while (!stream.atEnd()) {
		QString line = stream.readLine();
		logText->append(line);
	}
	file.close();
}

void LogWindow::fileOpen() {
	filename = QFileDialog::getOpenFileName(this, "Open log file");
	readFile();
	calculator->setResult(lastResult);
	filenameLabel->setText(filename);
}

void LogWindow::fileSave() {
	if (filename == "") {
		filename = QFileDialog::getSaveFileName(this, "Save log file");
		filenameLabel->setText(filename);
	}
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		return;
	}
	QTextStream stream(&file);
	stream << lastResult << "\n" << logText->toPlainText();
	file.close();
}

void LogWindow::revert() {
	logText->clear();
	if (filename == "") {
		lastResult = 0;
	} else {
		readFile();
	}
	calculator->setResult(lastResult);
}

void LogWindow::updateResult(double result) {
	lastResult = result;
	resultLabel->setNum(result);
}
