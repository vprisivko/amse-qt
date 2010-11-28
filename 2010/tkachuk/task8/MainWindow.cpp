#include <QtGui>
#include <QDockWidget>
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);

	createDockCalculator();
	createConnections();
	createStatusBar();

	myResult = 0;
}

void MainWindow::createConnections() {
	connect(ui.openAction, SIGNAL(triggered()), this, SLOT(open()));
	connect(ui.saveAction, SIGNAL(triggered()), this, SLOT(save()));
	connect(ui.revertAction, SIGNAL(triggered()), this, SLOT(revert()));
	connect(ui.calcAction, SIGNAL(triggered(bool)), dock, SLOT(setVisible(bool)));
	connect(dock, SIGNAL(visibilityChanged(bool)), ui.calcAction, SLOT(setChecked(bool)));
}

void MainWindow::createStatusBar() {
	logNameLabel = new QLabel("Log file name: ");
	logName= new QLabel("new file");
	lastResultLabel = new QLabel("Last result: ");
	lastResult = new QLabel("0");
	statusBar()->addWidget(logNameLabel);
	statusBar()->addWidget(logName);
	statusBar()->addWidget(lastResultLabel);
	statusBar()->addWidget(lastResult);

	connect(ui.myTextEdit, SIGNAL(textChanged()), this, SLOT(documentWasModified()));
}

void MainWindow::createDockCalculator() {
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

	dock = new QDockWidget("Calculator", this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea |
						   Qt::RightDockWidgetArea |
						   Qt::TopDockWidgetArea |
						   Qt::BottomDockWidgetArea);
	dock->setWidget(myCalculator);
	addDockWidget(Qt::RightDockWidgetArea, dock);
}

void MainWindow::plusPressed() {
	double b = QString(myInput->text()).toDouble();
	QString newCalc = QString::number(myResult).append(" + ").append(QString::number(b)).append(" = ")
			.append(QString::number(myResult + b));
	myResult += b;
	ui.myTextEdit->appendPlainText(newCalc);
}

void MainWindow::minusPressed() {
	double b = QString(myInput->text()).toDouble();
	QString newCalc = QString::number(myResult).append(" - ").append(QString::number(b)).append(" = ")
			.append(QString::number(myResult - b));
	myResult -= b;
	ui.myTextEdit->appendPlainText(newCalc);
}

void MainWindow::multPressed() {
	double b = QString(myInput->text()).toDouble();
	QString newCalc = QString::number(myResult).append(" * ").append(QString::number(b)).append(" = ")
			.append(QString::number(myResult * b));
	myResult *= b;
	ui.myTextEdit->appendPlainText(newCalc);
}

void MainWindow::dividePressed() {
	double b = QString(myInput->text()).toDouble();
	QString newCalc = QString::number(myResult).append(" / ").append(QString::number(b)).append(" = ")
			.append(QString::number(myResult / b));
	myResult /= b;
	ui.myTextEdit->appendPlainText(newCalc);
}

void MainWindow::documentWasModified() {
	lastResult->setText(QString::number(myResult));
}

void MainWindow::revert() {
	if(!curFile.isEmpty()) {
	 loadFile(curFile);
	} else {
		ui.myTextEdit->setPlainText("");
		myResult=0;
		lastResult->setText(QString::number(myResult));
	}
}

bool MainWindow::save() {
	if (curFile.isEmpty()) {
		QString fileName = QFileDialog::getSaveFileName(this, "Save log");
		if (fileName.isEmpty())
			return false;
		return saveFile(fileName);
	} else
		return saveFile(curFile);

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
	out << ui.myTextEdit->toPlainText();
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
		ui.myTextEdit->setPlainText(in.readAll());

	 curFile = fileName;
	 logName->setText(fileName);
 }
