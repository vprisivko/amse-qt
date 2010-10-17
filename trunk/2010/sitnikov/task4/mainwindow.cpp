#include <QTextStream>
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include "mainwindow.h"
#include "calcdialog.h"


MainWindow::MainWindow(QWidget *parent /* = 0 */) : QMainWindow(parent), openedFile_(""), lastResult_(0.0), revertState_(0)
{
	calculator_ = new CalcDialog(this);
	connect(calculator_, SIGNAL(evaluated(QString, double)), SLOT(evaluated(QString, double)));

	setWindowTitle("9375673");
	configureUI();
	updateStatusBar();
}

void MainWindow::configureUI()
{
	open_ = new QAction("&Open", this);
	save_ = new QAction("&Save", this);
	revert_ = new QAction("&Revert", this);
	calculate_ = new QAction("&Calculate...", this);
	exit_ = new QAction("E&xit", this);

	open_->setShortcuts(QKeySequence::Open);
	save_->setShortcuts(QKeySequence::Save);
	exit_->setShortcuts(QKeySequence::Quit);

	QMenu *menu = menuBar()->addMenu("&File");
	menu->addAction(open_);
	menu->addAction(save_);
	menu->addAction(revert_);
	menu->addSeparator();
	menu->addAction(exit_);
	menuBar()->addAction(calculate_);

	QToolBar *toolbar = addToolBar("toolBar");
	toolbar->addAction(open_);
	toolbar->addAction(save_);
	toolbar->addAction(revert_);
	toolbar->addSeparator();
	toolbar->addAction(calculate_);

	fileName_ = new QLabel(this);
	result_ = new QLabel(this);
	statusBar()->insertWidget(0, fileName_);
	statusBar()->insertPermanentWidget(1, result_);

	list_ = new QListWidget(this);
	setCentralWidget(list_);

	connect(open_, SIGNAL(triggered()), SLOT(file_open()));
	connect(save_, SIGNAL(triggered()), SLOT(file_save()));
	connect(revert_, SIGNAL(triggered()), SLOT(file_revert()));
	connect(calculate_, SIGNAL(triggered()), SLOT(main_calculate()));
	connect(exit_, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::updateStatusBar()
{
	fileName_->setText(openedFile_);
	result_->setText(QString::number(lastResult_));
}

void MainWindow::file_open()
{
	QString nfile = QFileDialog::getOpenFileName(this, "Open log file", QDir::homePath(), "log files (*.*)");
	QFile file(nfile);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::warning(this, windowTitle(), "Cannot open file " + nfile);
        return;
	} else {
		QTextStream stream(&file);
		list_->clear();
		if(stream.atEnd()) {
			lastResult_ = 0.0;
		} else {
			lastResult_ = stream.readLine().toDouble();
			while(!stream.atEnd()) list_->addItem(stream.readLine());
			int count = list_->count() - 1;
			if(count >= 0) lastResult_ = list_->item(count)->text().split(" ").last().toDouble();
		}
	}
	file.close();
	exprState_ = "";
	resultState_ = 0.0;
	revertState_ = 0;
	openedFile_ = nfile;
	updateStatusBar();
}

void MainWindow::file_save()
{
	if(revertState_ == 0) return;
	if(openedFile_ == "") {
		openedFile_ = QFileDialog::getSaveFileName(this, "Save log file", QDir::homePath(), "log files (*.*)");
		if(openedFile_ == "") return;
	}
	QFile file(openedFile_, this);
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QMessageBox::warning(this, windowTitle(), "Cannot save file " + openedFile_);
        return;
	} else {
		QTextStream stream(&file);
		stream << lastResult_ << "\n";
		for(int i = 0, _i = list_->count(); i != _i; ++i) {
			stream << list_->item(i)->text() << "\n";
		}
	}
	file.close();
	exprState_ = "";
	resultState_ = 0.0;
	revertState_ = 0;
	updateStatusBar();
}

void MainWindow::file_revert()
{
	if(revertState_ == 1) {
		int count = list_->count() - 1;
		exprState_ = list_->item(count)->text();
		resultState_ = exprState_.split(" ").last().toDouble();
		delete list_->takeItem(count);
		if(--count >= 0) {
			lastResult_ = list_->item(count)->text().split(" ").last().toDouble();
		} else {
			lastResult_ = 0.0;
		}
		revertState_ = 2;
	} else if(revertState_ == 2) {
		evaluated(exprState_, resultState_);
	}
	updateStatusBar();
}

void MainWindow::main_calculate()
{
	calculator_->setLastResult(lastResult_);
	calculator_->setVisible(!calculator_->isVisible());
}

void MainWindow::evaluated(QString expr, double result)
{
	list_->addItem(expr);
	revertState_ = 1;
	lastResult_ = result;
	updateStatusBar();
}
