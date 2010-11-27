#include "calccreator.h"

CalcCreator::CalcCreator(QWidget *parent)
    : QMainWindow(parent), m_fileName("Untitled")
{
	ui.setupUi(this);
	setWindowTitle("Calculator");
	ui.m_edit->setReadOnly(true);
    ui.menubar->addAction(ui.m_openCalcWidget);
	createStatusBar();
	createDockWidget();
	connectEvents();
}

void CalcCreator::createStatusBar(){
    m_logName = new QLabel(m_fileName, this);
    m_lastResult = new QLabel("Undefined", this);

    ui.statusbar->addWidget(new QLabel("Filename: ", this), 1);
    ui.statusbar->addWidget(m_logName);
    ui.statusbar->addWidget(new QLabel("Last result: ", this), 1);
    ui.statusbar->addWidget(m_lastResult);
}
void CalcCreator::createDockWidget(){
	m_calculator = new CalcDockWgt();
	ui.m_dockWgt->setWindowTitle("Calculator tool");
	ui.m_dockWgt->setWidget(m_calculator);
	ui.m_dockWgt->setAllowedAreas(Qt::AllDockWidgetAreas);

	QObject::connect(m_calculator, SIGNAL(plus_signal(double, double, double, char)), this, SLOT(writeLog(double, double, double, char)));
	QObject::connect(m_calculator, SIGNAL(minus_signal(double, double, double, char)), this, SLOT(writeLog(double, double, double, char)));
	QObject::connect(m_calculator, SIGNAL(multiply_signal(double, double, double, char)), this, SLOT(writeLog(double, double, double, char)));
	QObject::connect(m_calculator, SIGNAL(divide_signal(double, double, double, char)), this, SLOT(writeLog(double, double, double, char)));
}

void CalcCreator::connectEvents(){
	QObject::connect(ui.m_save, SIGNAL(triggered(bool)), this, SLOT(save()));
	QObject::connect(ui.m_open, SIGNAL(triggered(bool)), this, SLOT(open()));
	QObject::connect(ui.m_revert, SIGNAL(triggered(bool)), this, SLOT(revert()));
}
void CalcCreator::save(){
	if(m_fileName == "Untitled"){
		QString fileName = QFileDialog::getSaveFileName(this, "Save file",".","All files (*.ren)");
		if(fileName != "") m_fileName = fileName;
		m_logName->setText(m_fileName);
	}

    if(!m_fileName.endsWith(".ren")){
    	m_fileName.append(".ren");
    }

	if(m_fileName != "Untitled"){
		QFile file(m_fileName);
		file.open(QIODevice::ReadWrite);
        file.write((m_lastResult->text() + "\n").toUtf8());
		file.write(ui.m_edit->toPlainText().toUtf8());
		file.close();
	}
}
void CalcCreator::open(){
	QString fileName = QFileDialog::getOpenFileName(this, "Open file",".","All files (*.ren)");
	if(fileName != "") m_fileName = fileName;
	m_logName->setText(m_fileName);

	if(m_fileName != "Untitled"){
		QFile file(m_fileName);
		if(file.open(QIODevice::ReadWrite)){
			QString lastResult = QString(file.readLine());
			m_calculator->setLastResult(lastResult.toDouble());
			m_lastResult->setText(lastResult);
			ui.m_edit->setText(QString(file.readAll()));
			file.close();
		}
	}
}

void CalcCreator::revert(){
	if(m_fileName == "Untitled"){
		ui.m_edit->clear();
		m_calculator->setLastResult(NULL);
		m_lastResult->setText("Undefined");
		return;
	}
	QFile file(m_fileName);

	if(file.open(QIODevice::ReadWrite)){
		QString lastResult = QString(file.readLine());
		m_calculator->setLastResult(lastResult.toDouble());
		m_lastResult->setText(lastResult);
		ui.m_edit->setText(QString(file.readAll()));
		file.close();
	}
}

void CalcCreator::writeLog(double result, double secondOperand, double firstOperand, char sign) const {
	ui.m_edit->append(QString::number(firstOperand)+QString(sign)+QString::number(secondOperand)+"="+QString::number(result));
	m_lastResult->setText(QString::number(result));
}
