#include "MainWindow.h"
#include "Calculator.h"
#include <QtGui>


MainWindow :: MainWindow(QWidget *parant) : QMainWindow(parant) {

	setupUi(this);
	position = 0;
	calculator = new Calculator(this);

	createActions();

	readSettings();
}
void MainWindow :: closeEvent(QCloseEvent *) {
	writeSettings();
}
void MainWindow :: readSettings() {
	QSettings settings("Olenchuk", "Calculator");
	QPoint pos = settings.value("pos", QPoint(300, 300)).toPoint();
	QSize size = settings.value("size", QSize(400, 400)).toSize();
	resize(size);
	move(pos);
}
void MainWindow :: writeSettings() {
 	QSettings settings("Olenchuk", "Calculator");
	settings.setValue("pos", pos());
	settings.setValue("size", size());
}
void MainWindow::createActions() {
	connect(actionNewFile, SIGNAL(triggered()), this, SLOT(slotNewFile())); 
	connect(actionOpen, SIGNAL(triggered()), this, SLOT(slotOpenFile()));    
	connect(actionSave, SIGNAL(triggered()), this, SLOT(slotSaveFile()));
	connect(actionRevert, SIGNAL(triggered()), this, SLOT(slotRevertFile()));
	connect(actionCalculator, SIGNAL(triggered()), this, SLOT(slotShowCalculator()));
	connect(calculator, SIGNAL(answer(QString)), this, SLOT(answerWrite(QString)));
}
void MainWindow :: slotNewFile() {
	textEdit->clear();
	setCurrentFile("");
}
void MainWindow :: slotOpenFile() {
	QString fileName = QFileDialog::getOpenFileName(this);
	if (fileName.isEmpty()) {
		return;
	}
	QFile file(fileName);
	if (!file.open(QFile :: ReadOnly | QFile :: Text)) {
		return;
	}

	QTextStream in(&file);
	
	QApplication :: setOverrideCursor(Qt :: WaitCursor);
	textEdit->setPlainText(in.readAll());
	QApplication :: restoreOverrideCursor();


	setCurrentFile(fileName);
	statusbar->showMessage(tr("File loaded"), 3000);

	cursor = textEdit->textCursor();
	//textEdit->setTextCursor(cursor);
	cursor.movePosition(QTextCursor :: End);
	position = cursor.position();
	cursor.movePosition(QTextCursor :: PreviousWord, QTextCursor :: KeepAnchor);
	
	calculator->setSum(cursor.selectedText().toDouble());
}
void MainWindow :: slotSaveFile() { 
	QString fileName = QFileDialog::getSaveFileName(this, "XML files (*.xml)");
	if (fileName.isEmpty()) {
		return;
	}
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		return;
	}

	QTextStream out(&file);
	
	QApplication :: setOverrideCursor(Qt :: WaitCursor);
	out << textEdit->toPlainText();
	QApplication :: restoreOverrideCursor();
	
	setCurrentFile(fileName);
	statusbar->showMessage(tr("File saved"), 3000);
}
void MainWindow :: slotRevertFile() {
	cursor.setPosition(position);
	cursor.movePosition(QTextCursor::End, QTextCursor :: KeepAnchor);
	cursor.removeSelectedText();
	cursor.movePosition(QTextCursor :: PreviousWord, QTextCursor :: KeepAnchor);
	calculator->setSum(cursor.selectedText().toInt());
}
void MainWindow :: slotShowCalculator() {
	calculator->setVisible(true);
}
void MainWindow :: answerWrite(const QString &str) {
	textEdit->append(str);
}
void MainWindow :: setCurrentFile(const QString &fileName) {
	curFile = fileName;
	textEdit->document()->setModified(false);
	setWindowModified(false);

	QString shownName = curFile;
	if (curFile.isEmpty()) {
		shownName = "untitled.txt";
	}
	setWindowFilePath(shownName);
}


